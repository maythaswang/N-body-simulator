#ifndef RENDERER_H
#define RENDERER_H
#pragma once

#include <GLCommon.h>
#include <Shader/Shader.h>
#include <DisplaySystem/Camera/Camera.h>
#include <ParticleSystem/Simulator/Simulator.h>
#include <Mesh/RenderComponents.h>

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
     * @param window pointer to GLFWwindow
     * @param shader_program pointer to shader program
     * @param camera pointer to camera
     * @param simulator pointer to simulator
     * @param render_components stores rendering components like VAO, VBO,... for instancing
     */
    Renderer(GLFWwindow *, Shader *, Camera *, Simulator *, RenderComponents *);

    /**
     * @brief render the next frame.
     *
     */
    void render();

    /**
     * @brief Get the use_instancing state
     * 
     */
    bool get_use_instancing();

    /**
     * @brief Set the use_instancing state
     * @param use_instancing 
     * 
     */
    void set_use_instancing(bool use_instancing);

    /**
     * @brief Get the use_wireframe state
     * 
     */
    bool get_use_wireframe();

    /**
     * @brief Set the use_wireframe state
     * 
     * @param use_wireframe 
     */
    void set_use_wireframe(bool use_wireframe);

    bool get_use_msize();

    void set_use_msize(bool use_msize);

    bool get_use_bloom();
    
    void set_use_bloom(bool use_bloom);

    bool get_use_mcolor();

    void set_use_mcolor(bool use_mcolor);

private:
    GLFWwindow *window;
    Shader *shader_program;
    Camera *camera;
    Simulator *simulator;
    RenderComponents *render_components;

    // states
    bool use_wireframe;
    bool use_instancing;
    bool use_msize; // mass-size
    bool use_bloom;
    bool use_mcolor; // mass-color

    double start_time; // For calculating fps only
    double previous_time;
    long frame_count;

    /**
     * @brief Update the window name to show FPS and time elapsed.
     *
     */
    void show_fps();
};

#endif