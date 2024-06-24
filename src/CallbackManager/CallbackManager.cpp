#include <GLFW/glfw3.h>
#include <iostream> 
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        std::cout << "exit";
        glfwSetWindowShouldClose(window, true);
}