#pragma once
// Added guards just in case.
#ifndef display_h
#define display_h
#include <GLFW/glfw3.h>

namespace Display
{
    /**
     * @brief Create a Window object
     *
     * @return GLFWwindow*
     */
    GLFWwindow *CreateWindow(int, int, const char *);

    /**
     * @brief set the viewport size (this gets called automatically)
     *
     */
    void framebuffer_size_callback(GLFWwindow *, int, int);

};

#endif