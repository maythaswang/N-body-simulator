#pragma once
#include <GLCommon.h>
#include <Camera.h>
class DisplayManager
{
public:
    /**
     * @brief Construct a new Display Manager object
     *
     * @param window
     * @param camera
     */
    DisplayManager(GLFWwindow *, Camera);

private:
    GLFWwindow *window;
    Camera camera;

    void AllowResizable();
};