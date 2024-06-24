#include <GLAD/glad.h>
#include <Display.h>
#include <iostream>

GLFWwindow *Display::CreateWindow(int ScreenWidth, int ScreenHeight, const char *ScreenName)
{

    GLFWwindow *window = glfwCreateWindow(ScreenWidth, ScreenHeight, ScreenName, NULL, NULL);
    if (!window)
    {
        // TODO: Throw errors
        std::cout << "Screen cannot be initialized!";
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(window);

    // set to call framebuffer_size_callback everytime the screen gets resized
    glfwSetFramebufferSizeCallback(window, Display::framebuffer_size_callback);
    glfwSetWindowAspectRatio(window, ScreenWidth, ScreenHeight);

    return window;
}

void Display::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}