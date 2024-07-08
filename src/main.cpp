#include <GLCommon.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <ProgramInit.h>
#include <Shader.h>
#include <CallbackManager.h>
#include <Camera.h>
#include <WindowFactory.h>

#include <ParticleBuilder.h>
#include <Simulator.h>
#include <Renderer.h>
#include <StringCommon.h>
#include <ParticleParticleCPU.h>
#include <ParticleParticleGPU.h>

// For initialization
const unsigned int SCREEN_WIDTH = 640;
const unsigned int SCREEN_HEIGHT = 480;
const char *SCREEN_NAME = "N-BODY-SIMULATION";

void set_debug_mode(bool, bool, GLuint);
void sample_compute_shader(); // TODO: Delete this later (use as reference)

int main(int argc, char *argv[])
{
	std::cout << g_welcome_message << std::endl;
	std::cout << g_controls_help << std::endl;

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

	// The dir depends on where you call it so if you call it from root, do it as if the current working directory is in root.
	GLuint vertex_shader = shader_program.compile_shader("./shader_source/light.vert.glsl", GL_VERTEX_SHADER);
	GLuint fragment_shader = shader_program.compile_shader("./shader_source/light.frag.glsl", GL_FRAGMENT_SHADER);
	shader_program.link_shader(vertex_shader);
	shader_program.link_shader(fragment_shader);

	// Setup Required Components
	// ----------------------------------------------------------------------------
	Camera camera = Camera();

	ParticleBuilder particle_builder = ParticleBuilder();
	std::vector<glm::vec3> particle_position;
	std::vector<glm::vec3> particle_velocity;
	std::vector<glm::vec3> particle_acceleration;
	std::vector<GLfloat> particle_mass;
	GLuint n_particles;

	// TODO: DELETE THIS LATER
	// set_debug_mode(0,1,2);
	// sample_compute_shader();

	// TODO: DO SOMETHING, THESE ARE JUST TEMPORARY TESTERS
	// particle_builder.spawn_globular_cluster(500,glm::vec3(-550,-700,0),200,25,1000,100000,10,1000,false,true, false);
	// particle_builder.spawn_globular_cluster(500,glm::vec3(470,650,0),200,25,1000,100000,10,1000,false,true, false);

	// particle_builder.spawn_globular_cluster(1000,glm::vec3(0,0,0),200,25,1000,100000,-1000,1000,false,false, false);

	// particle_builder.spawn_globular_cluster(1000, glm::vec3(0, 0, 0), 700, 50, 1000, 100000, -1000, 1000, false, true, false);

	// particle_builder.spawn_globular_cluster(1000, glm::vec3(0, 0, 0), 500, 50, 1000, 100000, 0, 0, false, true, false);

	// particle_builder.spawn_random(100,glm::vec3(0.0f),500,1000,100000,0,1000);

	// particle_builder.spawn_globular_cluster(10000, glm::vec3(0, 0, 0), 700, 50, 1000, 100000, -1000, 1000, false, true, false);

	particle_builder.spawn_globular_cluster(10000, glm::vec3(0, 0, 0), 700, 50, 1000, 100000, -1000, 1000, false, false, false);

	if (!particle_builder.populate_vectors(&n_particles, &particle_position, &particle_velocity, &particle_acceleration, &particle_mass))
	{
		std::cout << "Failed to populate particles." << std::endl;
		return -1;
	}

	GLuint VAO, VBO;
	Simulator *simulator;
	// ParticleParticleCPU simulator_CPU = ParticleParticleCPU(1000, 0.8, 50, 0.001);
	// simulator = &simulator_CPU;

	ParticleParticleGPU simulator_GPU = ParticleParticleGPU(10000, 0.8, 50, 0.001);
	simulator = &simulator_GPU;

	simulator->load_particles(n_particles, particle_position, particle_velocity, particle_acceleration, particle_mass);
	simulator->initialize_particles(&VAO, &VBO);

	CallbackManager callback_manager = CallbackManager(window, &camera, simulator);
	Renderer renderer = Renderer(&callback_manager, window, &shader_program, &camera, simulator, VAO);

	// Begin Render Loop
	// ----------------------------------------------------------------------------
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

// TODO: Delete this later
void sample_compute_shader()
{
	Shader comp_shader_program = Shader();
	GLuint compute_shader = comp_shader_program.compile_shader("./shader_source/sample.comp.glsl", GL_COMPUTE_SHADER);
	comp_shader_program.link_shader(compute_shader);

	GLuint tmp_n = 64;
	std::vector<GLfloat> tmp_data(tmp_n);
	std::vector<GLfloat> tmp_data2(tmp_n);
	std::vector<GLfloat> tmp_data3(tmp_n);

	for (int i = 0; i < tmp_n; i++)
	{
		tmp_data[i] = i;
		tmp_data2[i] = 3;
		tmp_data3[i] = 2;
	}

	GLuint SSBO, SSBO2, SSBO3;

	glGenBuffers(1, &SSBO);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, SSBO);
	glBufferData(GL_SHADER_STORAGE_BUFFER, tmp_n * 1 * sizeof(GLfloat), &tmp_data[0], GL_DYNAMIC_COPY);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, SSBO);

	glGenBuffers(1, &SSBO2);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, SSBO2);
	glBufferData(GL_SHADER_STORAGE_BUFFER, tmp_n * 1 * sizeof(GLfloat), &tmp_data2[0],GL_DYNAMIC_COPY);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, SSBO2);

	glGenBuffers(1, &SSBO3);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, SSBO3);
	glBufferData(GL_SHADER_STORAGE_BUFFER, tmp_n * 1 * sizeof(GLfloat), &tmp_data3[0], GL_DYNAMIC_COPY);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, SSBO3);

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

	for (int runs = 0; runs < 10; runs++)
	{

		glBindBuffer(GL_SHADER_STORAGE_BUFFER, SSBO); // WHY DO I NEED TO PUT THIS???
		comp_shader_program.use();
		comp_shader_program.set_int("test_num", 1);
		glDispatchCompute(64, 1, 1);
		glMemoryBarrier(GL_UNIFORM_BARRIER_BIT);

		GLfloat *rtn = (GLfloat *)glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_ONLY);
		glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

		std::cout << std::endl;
		for (int i = 0; i < tmp_n; i++)
		{
			std::cout << rtn[i] << " ";
		}
		std::cout << std::endl;
	}
	comp_shader_program.delete_shader();
	// glDeleteBuffers(1, &VAO_tmp);
	glDeleteBuffers(1, &SSBO);
	glDeleteBuffers(1, &SSBO2);
	glDeleteBuffers(1, &SSBO3);
}