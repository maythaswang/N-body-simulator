#include <Display.h>
#include <iostream>

GLFWwindow *Display::CreateWindow(int ScreenWidth, int ScreenHeight, const char *ScreenName)
{

    GLFWwindow *window = glfwCreateWindow(ScreenWidth, ScreenHeight, ScreenName, NULL, NULL);
    if (!window)
    {
        // TODO: Throw errors
        std::cout << "Screen cannot be initialized!";
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowAspectRatio(window, ScreenWidth, ScreenHeight); 

    return window;
}
