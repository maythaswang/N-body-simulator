#pragma once
#include <GLCommon.h>
#include <Shader.h>
#include <Camera.h>
#include <Simulator.h>
#include <CallbackManager.h>
#include <RenderComponents.h>

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
     * @param render_components stores rendering components like VAO, VBO,... for instancing
     */
    Renderer(CallbackManager *, GLFWwindow *, Shader *, Camera *, Simulator *, RenderComponents *);

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
    RenderComponents *render_components;

    float use_instancing;
    double start_time; // For calculating fps only
    double previous_time;
    long frame_count;

    /**
     * @brief Update the window name to show FPS and time elapsed.
     *
     */
    void show_fps();

    void post_processing();
};