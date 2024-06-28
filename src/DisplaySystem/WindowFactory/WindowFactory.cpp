#include <WindowFactory.h>
#include <iostream>

WindowFactory::WindowFactory()
{
}

GLFWwindow *WindowFactory::create_window(int screen_width, int screen_height, const char *screen_name)
{

    GLFWwindow *window = glfwCreateWindow(screen_width, screen_height, screen_name, NULL, NULL);
    if (!window)
    {
        std::cout << "Screen cannot be initialized!";
        return NULL;
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowAspectRatio(window, screen_width, screen_height);
    return window;
}