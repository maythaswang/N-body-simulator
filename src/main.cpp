#define GLFW_INCLUDE_NONE
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
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
	
	// Verify that the window has been created properly
	if (!window)
	{	
		glfwTerminate();
		return -1;
	}

	Init::InitalizeGLAD();
	
	
	while (!glfwWindowShouldClose(window))
	{
		// Keep running
		processInput(window); // Maybe make a namespace for this 
	}

	std::cout << "Hello World";
	glfwTerminate();
	return 0;
}
