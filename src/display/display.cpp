#include <GLAD/glad.h>
#include <Display.h>
#include <iostream>

// FIXME: make this a class instead
GLFWwindow *Display::CreateWindow(int screenWidth, int screenHeight, const char *screenName)
{

    GLFWwindow *window = glfwCreateWindow(screenWidth, screenHeight, screenName, NULL, NULL);
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
    glfwSetWindowAspectRatio(window, screenWidth, screenHeight);

    return window;
}

// FIXME: Find a way to allow display to perform non-uniform resizing while retaining the correct aspect ratio of the object drawn
void Display::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}