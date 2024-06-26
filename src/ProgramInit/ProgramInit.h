#pragma once
#include <GLCommon.h>

namespace ProgramInit
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
     * @brief Function for GLFW error callback
     *
     */
    void error_callback(int, const char *);
}
