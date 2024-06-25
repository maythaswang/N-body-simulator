#pragma once
#include<GLCommon.h>
class CallbackManager
{
public:
    /**
     * @brief Construct a new Callback Manager
     * 
     * @param window 
     */
    CallbackManager(GLFWwindow *);

    /**
     * @brief Main function for processing input
     *
     */
    void processInput();

private:
    GLFWwindow *window;
};