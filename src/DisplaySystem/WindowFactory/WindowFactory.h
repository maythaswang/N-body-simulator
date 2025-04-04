#ifndef WINDOW_FACTORY_H
#define WINDOW_FACTORY_H

#include <GLCommon.h>

/**
 * @brief Used to build GLFWwindow
 * 
 */
class WindowFactory
{
public:
    /**
     * @brief Construct a new Window Factory object
     *
     */
    WindowFactory();
    
    /**
     * @brief Create a Window object
     *
     * @return GLFWwindow*
     */
    GLFWwindow *create_window(int, int, const char *);
};

#endif