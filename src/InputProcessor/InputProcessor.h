#ifndef INPUT_PROCESSOR_H
#define INPUT_PROCESSOR_H
#pragma once
#include <GLCommon.h>
#include <ParticleSystem/Simulator/Simulator.h>
#include <SetupSystem/SimulationLoader/SimulationLoader.h>
#include <Renderer/Renderer.h>
#include <Bloom/Bloom.h>

#include <StringCommon.h>

/**
 * @brief Basically store states of everything apart from camera stuffs
 * @note for camera stuffs I delegate everything to callback
 *
 */
class InputProcessor
{
public:
    InputProcessor(Simulator *simulator, Renderer *renderer, Bloom *bloom, Camera *camera, SimulationLoader *simulation_loader);
    ~InputProcessor();

    // Put on public so ImGui can edit this directly

    // Checkbox variable
    // I will use previous checking to avoid setting uniform every call
    // 0 = new, 1 = prev
    bool bloom_on[2] = {0, 0};
    bool instancing_on[2] = {0, 0};
    bool wireframe_on[2] = {0, 0};
    bool msize_on[2] = {0, 0};
    bool mcolor_on[2] = {0, 0};

    GLfloat renderer_gamma, bloom_gamma, renderer_exposure, bloom_exposure, bloom_blur_intensity;

    /**
     * @brief Compare new input with previous input and handle the toggling
     *
     */
    void process_input();

    void set_blur_intensity(GLfloat intensity);

    void set_gamma(GLfloat gamma);

    void set_exposure(GLfloat exposure);

    // Immediate functions (no need to check every loop, trigger when called)
    void imm_handle_show_setup_log();
    void imm_handle_show_help_msg();
    void imm_handle_gui_toggle();
    void imm_handle_camera_orbit_toggle();
    void imm_handle_camera_reset();

    // GUI exclusives
    void imm_update_bloom_gamma();
    void imm_update_bloom_exposure();
    void imm_update_bloom_blur_intensity();
    void imm_update_renderer_gamma();
    void imm_update_renderer_exposure();
    void imm_reset_renderer();
    void imm_reset_bloom();
    bool imm_save_simulator(std::string file_name);

    /**
     * @brief Handle simulation pausing
     *
     */
    void imm_handle_pause();

    // Get-Set
    bool get_simulator_running();
    bool get_gui_on();
    glm::vec3 get_camera_eye();
    glm::vec3 get_camera_center();
    glm::vec3 get_camera_up();
    bool get_camera_is_orbiting();

private:
    Simulator *simulator;
    Renderer *renderer;
    Bloom *bloom;
    Camera *camera;
    SimulationLoader * simulation_loader;

    // Read only form outside
    bool simulator_running = 0;
    bool gui_on = 1;

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
};

#endif