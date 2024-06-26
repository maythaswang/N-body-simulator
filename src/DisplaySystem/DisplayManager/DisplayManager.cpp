#include <DisplayManager.h>
#include <iostream>

DisplayManager::DisplayManager(GLFWwindow *window, Camera camera)
{
    this->window = window;
    this->camera = camera;

    this->AllowResizable();
}

void DisplayManager::AllowResizable()
{
    glfwSetWindowUserPointer(this->window, reinterpret_cast<void *>(this));

    // set to call this lambda function everytime the screen gets resized
    glfwSetFramebufferSizeCallback(this->window, [](GLFWwindow *window, int width, int height)
                                   { 
        // set the viewport size (this gets called automatically
        // This can be made as a function if it was a static function. (Since we're using class so we'll do it this way).
        DisplayManager * display_manager = reinterpret_cast<DisplayManager *> ( glfwGetWindowUserPointer ( window ));
        
        std::cout << display_manager << std::endl;
        
        if (display_manager) {
            display_manager->camera.setAspect( width, height );
        }
        glViewport(0, 0, width, height); });
}
