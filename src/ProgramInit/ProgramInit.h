#pragma once
#include <GLCommon.h>

namespace ProgramInit
{
    /**
     * @brief Initialize GLFW
     *
     */
    void initialize_glfw();

    /**
     * @brief Load all function pointers using GLAD
     *
     */
    void initialize_glad();

    /**
     * @brief Function for GLFW error callback
     *
     */
    void error_callback(int, const char *);
}
