#include <GLCommon.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <Init.h>
#include <CallbackManager.h>
#include <Shader.h>

#include <DisplayManager.h>
#include <WindowFactory.h>

// For initialization
const unsigned int SCREEN_WIDTH = 640;
const unsigned int SCREEN_HEIGHT = 480;
const char *SCREEN_NAME = "N-BODY-SIMULATION";

int main(int argc, char *argv[])
{

	// Initialization Subroutine
	// ----------------------------------------------------------------------------
	Init::InitializeGLFW();
	WindowFactory window_factory = WindowFactory();

	// Initialize Window
	GLFWwindow *window = window_factory.CreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_NAME);
	Camera camera = Camera();
	// Verify that the window has been created properly
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	Init::InitalizeGLAD();

	CallbackManager callback_manager = CallbackManager::CallbackManager(window);

	// Preparing shader program
	// ----------------------------------------------------------------------------

	Shader basic_shader = Shader::Shader();
	// The dir depends on where you call it so if you call it from root, do it as if the current working directory is in root.
	GLuint vertexShader = basic_shader.CompileShader("./shader_source/light.vert.glsl", GL_VERTEX_SHADER);
	GLuint fragmentShader = basic_shader.CompileShader("./shader_source/light.frag.glsl", GL_FRAGMENT_SHADER);
	basic_shader.LinkShader(vertexShader);
	basic_shader.LinkShader(fragmentShader);

	GLuint shader_program = basic_shader.GetShaderID();

	// TODO: Implement the projections to handle camera movement from here forward.

	// TODO: Remove this later when no longer needed and make one class to deal with creating Geometry, Transforming Geometry, and so on ...
	// Simple Geometry for testing.
	// ----------------------------------------------------------------------------

	GLuint VAOs; // VAO for each object
	GLuint VBOs; // Vertices, Indices, Colours
	GLuint EBOs; // Store Indices (How they link)

	GLfloat triangle_vert[3][3] = {
		{-0.5f, -0.5f, 0.0f},
		{0.5f, -0.5f, 0.0f},
		{0.0f, 0.5f, 0.0f}};

	GLuint triangle_inds[1][3] = {{0, 1, 2}};

	glGenVertexArrays(1, &VAOs);
	glGenBuffers(1, &VBOs);
	glGenBuffers(1, &EBOs);

	glBindVertexArray(VAOs);

	glBindBuffer(GL_ARRAY_BUFFER, VBOs);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 9, &triangle_vert[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 3, &triangle_inds[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	// Unbind VAOs, VBOs, EBOs
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Begin Render Loop
	// ----------------------------------------------------------------------------

	while (!glfwWindowShouldClose(window))
	{
		// Keep running
		callback_manager.processInput(); // Maybe have the window stored in it beforehand.
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shader_program);

		glBindVertexArray(VAOs);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// glDrawElements(GL_TRIANGLES, 0, 3, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Termination Subroutine
	// ----------------------------------------------------------------------------

	// Delete Buffers
	glDeleteVertexArrays(1, &VAOs);
	glDeleteBuffers(1, &VBOs);
	glDeleteBuffers(1, &EBOs);

	basic_shader.DeleteShader();
	glfwTerminate();
	return 0;
}
