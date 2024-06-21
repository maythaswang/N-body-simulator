// #pragma comment(lib, "glew32.lib")
#define GLFW_INCLUDE_NONE
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
// #include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Init.h>
#include <Display.h>
#include <CallbackManager.h>

// For initialization
const unsigned int SCREEN_WIDTH = 640;
const unsigned int SCREEN_HEIGHT = 480;
const char *SCREEN_NAME = "N-BODY-SIMULATION";

int main(int argc, char *argv[])
{
	Init::InitializeGLFW();

	// Initialize Window
	GLFWwindow *window = Display::CreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_NAME);
	if (!window)
	{	
		return -1;
	}

	Init::InitalizeGLAD();

	while (!glfwWindowShouldClose(window))
	{
		// Keep running
	}

	std::cout << "Hello World";
	glfwTerminate();
	return 0;
}
