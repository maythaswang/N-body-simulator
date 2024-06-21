#include <Init.h>
#include <iostream>

void Init::InitializeGLFW()
{
    if (!glfwInit())
    {
        std::cout << "Failed to initialize glfw.";
        // TODO: THROW ERRORS
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Maybe return something when error.
}

void Init::InitalizeGLAD()
{
	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		// Throw Error
	}
    // Maybe return something when error.
}