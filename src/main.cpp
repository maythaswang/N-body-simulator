#include <GLCommon.h>
#include <iostream>

#include <ProgramInit/ProgramInit.h>
#include <Shader/Shader.h>
#include <CallbackManager/CallbackManager.h>
#include <DisplaySystem/Camera/Camera.h>
#include <DisplaySystem/WindowFactory/WindowFactory.h>
#include <ParticleSystem/ParticleBuilder/ParticleBuilder.h>
#include <ParticleSystem/Simulator/Simulator.h>

#include <Renderer/Renderer.h>
#include <StringCommon.h>
#include <ParticleSystem/ParticleParticleCPU/ParticleParticleCPU.h>
#include <ParticleSystem/ParticleParticleGPU/ParticleParticleGPU.h>
#include <SetupSystem/InputParser/InputParser.h>
#include <Mesh/MeshBuilder.h>
#include <Bloom/Bloom.h>
#include <InputProcessor/InputProcessor.h>
#include <GUI/GUI.h>

// For initialization
const unsigned int SCREEN_WIDTH = 640;
const unsigned int SCREEN_HEIGHT = 480;
const GLfloat SOFTENING_FACTOR = 50;
const char *SCREEN_NAME = "N-BODY-SIMULATION";

void print_workgroup_info();
void terminate(RenderComponents *render_components);

int main(int argc, char *argv[])
{
	// Accept Inputs
	// ----------------------------------------------------------------------------
	std::cout << g_welcome_message << std::endl;
	ParticleBuilder particle_builder = ParticleBuilder();
	InputParser input_parser = InputParser(&particle_builder);
	input_parser.accept_input();
	std::string setup_log_head = "+------------------------------------------------+\n"
								 "| Setup Summary                                  |\n"
								 "+------------------------------------------------+\n";
	std::string setup_log_input = input_parser.get_summary();
	std::string setup_log_particle = particle_builder.get_summary();

	// Initialization Subroutine
	// ----------------------------------------------------------------------------
	ProgramInit::initialize_glfw();
	WindowFactory window_factory = WindowFactory();
	GLFWwindow *window = window_factory.create_window(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_NAME);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	ProgramInit::initialize_glad();

	// Preparing shader program
	// ----------------------------------------------------------------------------

	Shader shader_program = Shader();

	// TODO: Bake the shaders in.

	// The dir depends on where you call it so if you call it from root, do it as if the current working directory is in root.
	GLuint vertex_shader = shader_program.compile_shader("./shader_source/light.vs", GL_VERTEX_SHADER);
	GLuint fragment_shader = shader_program.compile_shader("./shader_source/light.fs", GL_FRAGMENT_SHADER);
	shader_program.link_shader(vertex_shader);
	shader_program.link_shader(fragment_shader);

	// Setup Required Components
	// ----------------------------------------------------------------------------
	Camera camera = Camera();

	// Initialize particle data
	std::vector<glm::vec4> particle_position;
	std::vector<glm::vec4> particle_velocity;
	std::vector<glm::vec4> particle_acceleration;
	std::vector<GLfloat> particle_mass;
	GLuint n_particles;

	if (!particle_builder.populate_vectors(&n_particles, &particle_position, &particle_velocity, &particle_acceleration, &particle_mass))
	{
		std::cout << "Failed to populate particles." << std::endl;
		return -1;
	}

	// Storing particle information
	GLuint particle_position_SSBO, particle_mass_SSBO;
	Simulator *simulator;

	// Sphere mesh
	MeshBuilder mesh_builder;
	RenderComponents render_components = mesh_builder.build_sphere(1, 12, 8);

	// Simulator setup
	SimulatorIntegrator integrator = (input_parser.get_use_velocity_verlet()) ? INTEGRATOR_VELOCITY_VERLET : INTEGRATOR_EULER;
	GLfloat gravitational_constant = input_parser.get_gravitational_constant();
	GLfloat timestep_size = input_parser.get_timestep_size();

	// TODO: CHANGE THIS TO SMART POINTER LATER ON
	if (!input_parser.get_use_GPU())
	{
		simulator = new ParticleParticleCPU(n_particles, gravitational_constant, SOFTENING_FACTOR, timestep_size, integrator);
	}
	else
	{
		ParticleParticleGPU simulator_GPU = ParticleParticleGPU(n_particles, gravitational_constant, SOFTENING_FACTOR, timestep_size, integrator);
		simulator = new ParticleParticleGPU(n_particles, gravitational_constant, SOFTENING_FACTOR, timestep_size, integrator);
	}

	simulator->load_particles(n_particles, particle_position, particle_velocity, particle_acceleration, particle_mass);

	// TODO: This is just here for setting up the logs  (we will do it such that the same input can be import/ export later)
	simulator->append_setup_log(setup_log_head);
	simulator->append_setup_log(setup_log_input);
	simulator->append_setup_log(setup_log_particle);
	simulator->append_setup_log("\n--------------------------------------------------\n\n");

	Renderer renderer = Renderer(window, &shader_program, &camera, simulator, &render_components);

	// Post Processor
	// ----------------------------------------------------------------------------
	Bloom bloom = Bloom(SCREEN_WIDTH, SCREEN_HEIGHT);

	// Input Management
	InputProcessor input_processor = InputProcessor(simulator, &renderer, &bloom, &camera);
	
	CallbackManager callback_manager = CallbackManager(window, &camera, &input_processor, &bloom);
	GUI gui = GUI(window, &input_processor);
	// Begin Render Loop
	// ----------------------------------------------------------------------------

	// print_workgroup_info();
	std::cout << simulator->get_setup_log() << std::endl;
	std::cout << g_controls_help << std::endl;
	std::cout << "Starting Simulator in paused state..." << std::endl;

	while (!glfwWindowShouldClose(window))
	{
		// Process Input
		glfwPollEvents();
		callback_manager.process_input();
		input_processor.process_input();

		// Post Processing setup
		if (bloom.get_enabled())
		{
			bloom.bind_render_FBO();
		}
		// Draw
		renderer.render();

		// Post Processing
		if (bloom.get_enabled())
		{
			bloom.apply_effect();
			bloom.bind_default_FBO();
			bloom.draw_result();
		}

		gui.render_gui();
		glfwSwapBuffers(window);
	}

	// Termination Subroutine
	// ----------------------------------------------------------------------------

	std::cout << "Terminating..." << std::endl;
	gui.terminate();
	terminate(&render_components);
	shader_program.delete_shader();
	simulator->terminate();
	delete simulator;
	bloom.terminate();
	glfwTerminate();
	return 0;
}

void terminate(RenderComponents *render_components)
{
	glDeleteVertexArrays(1, &render_components->VAO);
	glDeleteBuffers(1, &render_components->VBO);
	glDeleteBuffers(1, &render_components->EBO);
}

void print_workgroup_info()
{
	int max_compute_work_group_count[3];
	int max_compute_work_group_size[3];
	int max_compute_work_group_invocations;

	ProgramInit::get_max_workgroup_info(max_compute_work_group_count, max_compute_work_group_size, &max_compute_work_group_invocations);

	std::cout << "maximum number of work groups: " << max_compute_work_group_count[0] << max_compute_work_group_count[1] << max_compute_work_group_count[2] << std::endl;
	std::cout << "maximum size of a work group: " << max_compute_work_group_size[0] << max_compute_work_group_size[1] << max_compute_work_group_size[2] << std::endl;
	std::cout << "maximum number of invocations: " << max_compute_work_group_invocations << std::endl;
}
