#include <iostream>
#include <CallbackManager.h>

CallbackManager::CallbackManager(GLFWwindow *window)
{
    this->window = window;
};


void CallbackManager::processInput()
{
    // TODO: Maybe accept class like CameraController to control camera based on input.
    GLFWwindow * window = this->window;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}