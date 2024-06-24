#include <GLFW/glfw3.h>
#include <iostream> 
void processInput(GLFWwindow *window)
{
    // TODO: Maybe accept class like CameraController to control camera based on input.

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        std::cout << "exit";
        glfwSetWindowShouldClose(window, true);
}