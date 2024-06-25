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
        // TODO: Throw errors
        std::cout << "Screen cannot be initialized!";
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(window);

    // set to call this lambda function everytime the screen gets resized
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int width, int height)
                                   { 
        // set the viewport size (this gets called automatically
        // This can be made as a function if it was a static function. (Since we're using class so we'll do it this way).
        // TODO: Fix the aspect ratio issue. (Maybe try change a global variable or call a static fn that forces the camera object to change.)
        glViewport(0, 0, width, height); });

    glfwSetWindowAspectRatio(window, screenWidth, screenHeight);

    return window;
}