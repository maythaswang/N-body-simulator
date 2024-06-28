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

// For initialization
const unsigned int SCREEN_WIDTH = 640;
const unsigned int SCREEN_HEIGHT = 480;
const char *SCREEN_NAME = "N-BODY-SIMULATION";

int main(int argc, char *argv[])
{

	// Initialization Subroutine
	// ----------------------------------------------------------------------------
	ProgramInit::initialize_glfw();
	WindowFactory window_factory = WindowFactory();

	// Initialize Window
	GLFWwindow *window = window_factory.create_window(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_NAME);

	// Verify that the window has been created properly
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	ProgramInit::initialize_glad();


	// Preparing shader program
	// ----------------------------------------------------------------------------

	Shader shader_program = Shader::Shader();
	// The dir depends on where you call it so if you call it from root, do it as if the current working directory is in root.
	GLuint vertexShader = shader_program.compile_shader("./shader_source/light.vert.glsl", GL_VERTEX_SHADER);
	GLuint fragmentShader = shader_program.compile_shader("./shader_source/light.frag.glsl", GL_FRAGMENT_SHADER);
	shader_program.link_shader(vertexShader);
	shader_program.link_shader(fragmentShader);

	GLuint shader_id = shader_program.get_shader_id();

	// TODO: Implement the projections to handle camera movement from here forward.
	Camera camera = Camera();
	Camera* p_camera = &camera; 
	CallbackManager callback_manager = CallbackManager::CallbackManager(window, p_camera);

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
		callback_manager.process_input();
		shader_program.set_mat4("modelview", camera.get_view_matrix() * camera.get_model_matrix());
		shader_program.set_mat4("projection", camera.get_projection_matrix());
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shader_id);
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

	shader_program.delete_shader();
	glfwTerminate();
	return 0;
}
