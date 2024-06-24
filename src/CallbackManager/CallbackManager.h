#pragma once
#include <GLFW/glfw3.h>
class CallbackManager
{
public:
    /**
     * @brief Construct a new Callback Manager object
     *
     */
    CallbackManager(){};

    /**
     * @brief Main function for processing input 
     * 
     */
    void processInput(GLFWwindow *);
};