#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
namespace Init
{
    /**
     * @brief Initialize GLFW
     *
     */
    void InitializeGLFW();

    /**
     * @brief Load all function pointers using GLAD
     *
     */
    void InitalizeGLAD();

    /**
     * @brief Set the Error Callback for GLFW
     *
     */
    void SetErrorCallback();

    /**
     * @brief Function for GLFW error callback 
     * 
     */
    void error_callback(int, const char*);
}
