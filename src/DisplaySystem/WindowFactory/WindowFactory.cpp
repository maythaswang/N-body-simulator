#include <WindowFactory.h>
#include <iostream>

WindowFactory::WindowFactory()
{
}

GLFWwindow *WindowFactory::CreateWindow(int screenWidth, int screenHeight, const char *screenName)
{

    GLFWwindow *window = glfwCreateWindow(screenWidth, screenHeight, screenName, NULL, NULL);
    if (!window)
    {
        std::cout << "Screen cannot be initialized!";
        return NULL;
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowAspectRatio(window, screenWidth, screenHeight);
    return window;
}