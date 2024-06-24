#pragma once
// Added guards just in case.
#ifndef DISPLAY_H
#define DISPLAY_H
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
}

#endif