#include <iostream>
#include <CallbackManager.h>

CallbackManager::CallbackManager(GLFWwindow *window, Camera camera)
{
    this->window = window;
    this->camera = camera;

    this->SetWindowResizeCallback();
};

void CallbackManager::processInput()
{
    GLFWwindow *window = this->window;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void CallbackManager::SetWindowResizeCallback()
{
    glfwSetWindowUserPointer(this->window, reinterpret_cast<void *>(this));

    // set to call this lambda function everytime the screen gets resized
    // This can be made as a normal function if it was a static function.
    glfwSetFramebufferSizeCallback(this->window, [](GLFWwindow *window, int width, int height)
                                   { 
        
        // Set the camera aspect ratio
        CallbackManager * callback_manager = reinterpret_cast<CallbackManager *> ( glfwGetWindowUserPointer ( window ));
        if (callback_manager) callback_manager->camera.setAspect( width, height );
        
        // set the viewport size
        glViewport(0, 0, width, height); });
}