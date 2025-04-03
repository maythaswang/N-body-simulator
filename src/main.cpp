#include <GLCommon.h>
#include <iostream>

#include <ProgramInit.h>
#include <Shader.h>
#include <CallbackManager.h>
#include <Camera.h>
#include <WindowFactory.h>
#include <ParticleBuilder.h>
#include <Simulator.h>

#include <Renderer.h>
#include <StringCommon.h>
// #include <ParticleParticleCPU.h>
#include <ParticleParticleGPU.h>
#include <InputParser.h>

// For initialization
const unsigned int SCREEN_WIDTH = 640;
const unsigned int SCREEN_HEIGHT = 480;
const GLfloat SOFTENING_FACTOR = 50;
const char *SCREEN_NAME = "N-BODY-SIMULATION";

void set_debug_mode(bool, bool, GLuint);

// TODO: Implement visual effects (eg: bloom, particle colour based on mass or stellar class...)

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

	//TODO: Bake the shaders in.

	// The dir depends on where you call it so if you call it from root, do it as if the current working directory is in root.
	GLuint vertex_shader = shader_program.compile_shader("./shader_source/light.vert.glsl", GL_VERTEX_SHADER);
	GLuint fragment_shader = shader_program.compile_shader("./shader_source/light.frag.glsl", GL_FRAGMENT_SHADER);
	shader_program.link_shader(vertex_shader);
	shader_program.link_shader(fragment_shader);

	// Setup Required Components
	// ----------------------------------------------------------------------------
	Camera camera = Camera();

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

	// TODO: Use this buffer to store the mesh information for instancing instead.
	GLuint VAO, VBO;
	Simulator *simulator;

	SimulatorIntegrator integrator = (input_parser.get_use_velocity_verlet()) ? INTEGRATOR_VELOCITY_VERLET : INTEGRATOR_EULER;
	GLfloat gravitational_constant = input_parser.get_gravitational_constant();
	GLfloat timestep_size = input_parser.get_timestep_size();

	// WARNING: DISABLE CPU IMPLEMENTATION FORNOW
	// if (!input_parser.get_use_GPU())
	// {
	// 	ParticleParticleCPU simulator_CPU = ParticleParticleCPU(n_particles, gravitational_constant, SOFTENING_FACTOR, timestep_size, integrator);
	// 	simulator = &simulator_CPU;
	// }
	// else
	// {
		ParticleParticleGPU simulator_GPU = ParticleParticleGPU(n_particles, gravitational_constant, SOFTENING_FACTOR, timestep_size, integrator);
		simulator = &simulator_GPU;
	// }

	simulator->load_particles(n_particles, particle_position, particle_velocity, particle_acceleration, particle_mass);
	simulator->initialize_particles(&VAO, &VBO);

	simulator->append_setup_log(setup_log_head);
	simulator->append_setup_log(setup_log_input);
	simulator->append_setup_log(setup_log_particle);
	simulator->append_setup_log("\n--------------------------------------------------\n\n");

	CallbackManager callback_manager = CallbackManager(window, &camera, simulator);
	Renderer renderer = Renderer(&callback_manager, window, &shader_program, &camera, simulator, VAO);

	// Begin Render Loop
	// ----------------------------------------------------------------------------
	
	// set_debug_mode(0,1,2);
	std::cout << simulator->get_setup_log() << std::endl;
	std::cout << g_controls_help << std::endl;
	std::cout << "Starting Simulator in paused state..." << std::endl;
	while (!glfwWindowShouldClose(window))
	{
		renderer.render();
	}

	// Termination Subroutine
	// ----------------------------------------------------------------------------

	std::cout << "Terminating..." << std::endl;

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	shader_program.delete_shader();
	simulator->terminate();
	glfwTerminate();
	return 0;
}

void set_debug_mode(bool wireframe_on, bool point_size_on, GLuint point_size)
{
	if (wireframe_on)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	if (point_size_on)
	{
		glPointSize(point_size);
	}

	int max_compute_work_group_count[3];
	int max_compute_work_group_size[3];
	int max_compute_work_group_invocations;

	ProgramInit::get_max_workgroup_info(max_compute_work_group_count, max_compute_work_group_size, &max_compute_work_group_invocations);

	std::cout << "maximum number of work groups: " << max_compute_work_group_count[0] << max_compute_work_group_count[1] << max_compute_work_group_count[2] << std::endl;
	std::cout << "maximum size of a work group: " << max_compute_work_group_size[0] << max_compute_work_group_size[1] << max_compute_work_group_size[2] << std::endl;
	std::cout << "maximum number of invocations: " << max_compute_work_group_invocations << std::endl;
}
