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

    glfwSetErrorCallback(error_callback);

    // Maybe return something when error.
}
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

void Init::InitalizeGLAD()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		// TODO: THROW ERRORS
	}

    // Maybe return something when error.
}

void Init::error_callback(int error, const char* description) {
    fprintf(stderr, "Error %s\n", description);
}
