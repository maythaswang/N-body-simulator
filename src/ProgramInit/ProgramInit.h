#pragma once
#include <GLCommon.h>

/**
 * @brief Initializes the libraries required.
 *
 */
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
     * @param error
     * @param description
     * 
     */
    void error_callback(int, const char *);

    /**
     * @brief Put the information about maximum value (number, size, invocations) of a workgroup into the arrays specified.
     *
     */
    void get_max_workgroup_info(int[3], int[3], int *);
}
