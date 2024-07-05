#pragma once
#include <GLCommon.h>
#include <Shader.h>
#include <Camera.h>
#include <Simulator.h>
#include <CallbackManager.h>

/**
 * @brief Handle rendering frames onto window.
 *
 */
class Renderer
{
public:
    /**
     * @brief Construct a new Renderer object 
     * @warning All these components must came from the same set, otherwise unexpected behaviour may occurs. 
     *
     * @param callback_manager pointer to callback manager 
     * @param window pointer to GLFWwindow
     * @param shader_program pointer to shader program
     * @param camera pointer to camera
     * @param simulator pointer to simulator
     * @param VAO VAO storing the particle positions
     */
    Renderer(CallbackManager *, GLFWwindow *, Shader *, Camera *, Simulator *, GLuint);

    /**
     * @brief render the next frame.
     *
     */
    void render();

private:
    GLFWwindow *window;
    Shader *shader_program;
    Camera *camera;
    Simulator *simulator;
    CallbackManager *callback_manager;
    GLuint VAO;
};