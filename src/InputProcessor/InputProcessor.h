#ifndef INPUT_PROCESSOR_H
#define INPUT_PROCESSOR_H
#pragma once
#include <GLCommon.h>
#include <ParticleSystem/Simulator/Simulator.h>
#include <Renderer/Renderer.h>
#include <Bloom/Bloom.h>

/**
 * @brief Basically store states of everything
 * 
 */
class InputProcessor
{
public:
    InputProcessor(Simulator *simulator, Renderer *renderer, Bloom *bloom);
    ~InputProcessor();

    // Put on public so ImGui can edit this directly

    // Hotkeys only
    bool gui_on;

    // Button variable
    bool pause_on;

    // Checkbox variable
    // I will use previous checking to avoid setting uniform every call
    bool instancing_on[2];
    bool wireframe_on[2];
    bool msize_on[2];
    bool mcolor_on[2];

    /**
     * @brief Compare new input with previous input and handle the toggling
     * 
     */
    void process_input();

    /**
     * @brief Handle simulation pausing
     *
     */
    void handle_pause();

    /**
     * @brief Handle toggling renderer instancing mode
     * 
     */
    void handle_instancing_toggle();

    /**
     * @brief Handle toggling renderer wireframe mode
     * 
     */
    void handle_wireframe_toggle();

    /**
     * @brief Handle toggling bloom
     * 
     */
    void handle_bloom_toggle();

    /**
     * @brief Handle toggling renderer mass-size
     * 
     */
    void handle_msize_toggle();

    /**
     * @brief Handle toggling renderer mass-color
     * 
     */
    void handle_mcolor_toggle();

    void handle_show_setup_log();

    void handle_show_help_msg();

    void handle_gui_toggle();

    void set_blur_intensity(GLfloat intensity);

    void set_gamma(GLfloat gamma);

    void set_exposure(GLfloat exposure);

private:

};

#endif