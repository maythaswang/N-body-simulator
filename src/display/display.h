#pragma once
// Added guards just in case.
#ifndef DISPLAY_H
#define DISPLAY_H
// #include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Display
{
    /**
     * @brief Create a Window object
     *
     * @return GLFWwindow*
     */
    GLFWwindow *CreateWindow(int, int, const char*);
}

#endif