#include <iostream> 
#include <CallbackManager.h>

void CallbackManager::processInput(GLFWwindow *window)
{
    // TODO: Maybe accept class like CameraController to control camera based on input.

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        std::cout << "exit";
        glfwSetWindowShouldClose(window, true);
}