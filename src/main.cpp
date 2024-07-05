#include <GLCommon.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <ProgramInit.h>
#include <Shader.h>
#include <Particle.h>
#include <CallbackManager.h>
#include <Camera.h>
#include <WindowFactory.h>

#include <Simulator.h>
#include <Renderer.h>
#include <StringCommon.h>

// For initialization
const unsigned int SCREEN_WIDTH = 640;
const unsigned int SCREEN_HEIGHT = 480;
const char *SCREEN_NAME = "N-BODY-SIMULATION";
const bool WIREFRAME_ON = true;
const bool POINT_SIZE_ON = false;

const std::string welcome_message ="";

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
	GLuint vertexShader = shader_program.compile_shader("./shader_source/light.vert.glsl", GL_VERTEX_SHADER);
	GLuint fragmentShader = shader_program.compile_shader("./shader_source/light.frag.glsl", GL_FRAGMENT_SHADER);
	shader_program.link_shader(vertexShader);
	shader_program.link_shader(fragmentShader);

	// Settings for test.
	// ----------------------------------------------------------------------------

	if (WIREFRAME_ON)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	if (POINT_SIZE_ON)
	{
		glPointSize(1);
	}

	// Setup Required Components
	// ----------------------------------------------------------------------------
	Camera camera = Camera();

	GLuint VAO, VBO;
	Simulator simulator = Simulator(1000, 0.8, 15, 0.001);
	simulator.initialize_particles(&VAO, &VBO);

	CallbackManager callback_manager = CallbackManager(window, &camera, &simulator);
	// Renderer renderer = Renderer(&callback_manager, window, &shader_program, &camera, &simulator, VAO); // FIXME: Renderer class currently doesn't work

	// Begin Render Loop
	// ----------------------------------------------------------------------------
	while (!glfwWindowShouldClose(window))
	{
		callback_manager.process_input();
		shader_program.set_mat4("modelview", camera.get_view_matrix() * camera.get_model_matrix());
		shader_program.set_mat4("projection", camera.get_projection_matrix());
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shader_program.use();

		glBindVertexArray(VAO);
		glDrawArrays(GL_POINTS, 0, 1000);
		glfwSwapBuffers(window);

		if (simulator.get_running_state())
		{
			simulator.next_step();
		}
		glfwPollEvents();
	}

	// Termination Subroutine
	// ----------------------------------------------------------------------------

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	shader_program.delete_shader();
	glfwTerminate();
	return 0;
}
