#pragma once
#include<GLCommon.h>
#include <Camera.h>
class CallbackManager
{
public:
    /**
     * @brief Construct a new Callback Manager
     * 
     * @param window 
     * @param camera
     */
    CallbackManager(GLFWwindow *, Camera *);

    /**
     * @brief Main function for processing input
     *
     */
    void processInput();

private:
    GLFWwindow *window;
    Camera *camera;

    /**
     * @brief Set the window and camera aspect ratio when framebuffer gets resized.
     * 
     */
    void SetWindowResizeCallback();
};