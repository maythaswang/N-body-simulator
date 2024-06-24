#define GLFW_INCLUDE_NONE
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>

#include <Init.h>
#include <Display.h>
#include <CallbackManager.h>
#include <Shader.h>

// For initialization
const unsigned int SCREEN_WIDTH = 640;
const unsigned int SCREEN_HEIGHT = 480;
const char *SCREEN_NAME = "N-BODY-SIMULATION";

int main(int argc, char *argv[])
{

	// Initialization Subroutine
	// ----------------------------------------------------------------------------
	Init::InitializeGLFW();

	// Initialize Window
	GLFWwindow *window = Display::CreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_NAME);

	// Verify that the window has been created properly
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	Init::InitalizeGLAD();

	CallbackManager callback_manager = CallbackManager::CallbackManager();

	// Preparing shader program
	// ----------------------------------------------------------------------------

	Shader basic_shader = Shader::Shader();
	// The dir depends on where you call it so if you call it from root, do it as if the current working directory is in root.
	GLuint vertexShader = basic_shader.CompileShader("./shader_source/light.vert.glsl", GL_VERTEX_SHADER);
	GLuint fragmentShader = basic_shader.CompileShader("./shader_source/light.frag.glsl", GL_FRAGMENT_SHADER);
	basic_shader.LinkShader(vertexShader);
	basic_shader.LinkShader(fragmentShader);

	GLuint shader_program = basic_shader.GetShaderID();

	// TODO: Remove this later
	// Simple Geometry for testing.
	// ----------------------------------------------------------------------------

	// Begin Render Loop
	// ----------------------------------------------------------------------------

	while (!glfwWindowShouldClose(window))
	{
		// Keep running
		callback_manager.processInput(window); // Maybe have the window stored in it beforehand.
	}

	std::cout << "Hello World";

	// Termination Subroutine
	// ----------------------------------------------------------------------------
	basic_shader.DeleteShader();
	glfwTerminate();
	return 0;
}
