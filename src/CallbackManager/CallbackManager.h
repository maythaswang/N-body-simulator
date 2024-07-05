#pragma once
#include <GLCommon.h>
#include <Camera.h>
#include <CameraEnum.h>
#include <Simulator.h>

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
    CallbackManager(GLFWwindow *, Camera *, Simulator *);

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

    // Mouse states

    bool middle_mouse_down;
    bool left_shift_down; // for translation
    bool left_ctrl_down;  // for zoom

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
     * @brief Update the camera mode accordingly
     *
     */
    void update_camera_mode();

    /**
     * @brief Call functions required to update the camera position based on the modes.
     *
     */
    void update_camera_position();
};