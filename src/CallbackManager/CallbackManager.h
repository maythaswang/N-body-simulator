#ifndef CALLBACK_MANAGER_H
#define CALLBACK_MANAGER_H
#pragma once

#include <GLCommon.h>
#include <DisplaySystem/Camera/Camera.h>
#include <ParticleSystem/Simulator/Simulator.h>
#include <Renderer/Renderer.h>
#include "CameraEnum.h"

/**
 * @brief Handle Callbacks recieved from window, mouse, keyboards and update the components accordingly
 *
 */
class CallbackManager
{
public:
    /**
     * @brief Construct a new Callback Manager
     *
     * @param window glfw window where we want to use as our display window
     * @param camera the current camera
     */
    CallbackManager(GLFWwindow *, Camera *, Simulator *, Renderer *);

    /**
     * @brief Main function for processing input
     *
     */
    void process_input();

private:
    GLFWwindow *window;
    Camera *camera;
    CameraMode camera_mode;
    Simulator *simulator;
    Renderer *renderer;

    // Mouse states

    bool middle_mouse_down;
    bool left_shift_down; // for translation
    bool left_ctrl_down;  // for zoom

    bool camera_orbiting;

    double old_mouse_pos_x;
    double old_mouse_pos_y;

    double mouse_pos_x;
    double mouse_pos_y;

    /**
     * @brief Handle each mouse and keyboard input accordingly.
     *
     */
    void handle_input();

    /**
     * @brief Set the window and camera aspect ratio when framebuffer gets resized.
     *
     */
    void set_window_resize_callback();

    /**
     * @brief Set the cursor position callback.
     *
     */
    void set_cursor_position_callback();

    /**
     * @brief Set the keyboard callback.
     *
     */
    void set_keyboard_callback();

    /**
     * @brief Set the mouse scroll callback
     *
     */
    void set_scroll_callback();

    /**
     * @brief Update the camera mode accordingly
     *
     */
    void update_camera_mode();

    /**
     * @brief Call functions required to update the camera position based on the modes.
     *
     */
    void update_camera_position();

    /**
     * @brief Set the camera status to orbiting / free
     *
     * @param camera_orbiting {0: free mode, 1: orbit mode}
     */
    void set_camera_orbiting(bool);

    /**
     * @brief Get camera orbiting status
     *
     * @return 1 if camera is in orbit mode
     */
    bool get_camera_orbiting();

    /**
     * @brief Handle simulation pausing
     *
     */
    void handle_pause();

    void handle_orbit_toggle();
    void handle_instancing_toggle();
    void handle_wireframe_toggle();
};

#endif