#pragma once
#include <GLCommon.h>
#include <Camera.h>
#include <CameraEnum.h>
class CallbackManager
{
public:
    /**
     * @brief Construct a new Callback Manager
     *
     * @param window
     * @param camera
     */
    CallbackManager(GLFWwindow *, Camera *);

    /**
     * @brief Main function for processing input
     *
     */
    void ProcessInput();

private:
    GLFWwindow *window;
    Camera *camera;
    CameraMode cameraMode;

    // Mouse states

    bool middleMouseDown;
    bool leftShiftDown; // for translation
    bool leftCtrlDown;  // for zoom

    double old_mouse_pos_x;
    double old_mouse_pos_y;
    
    double mousePosX;
    double mousePosY;

    /**
     * @brief Handle each mouse and keyboard input accordingly.
     *
     */
    void HandleInput();

    /**
     * @brief Set the window and camera aspect ratio when framebuffer gets resized.
     *
     */
    void SetWindowResizeCallback();

    /**
     * @brief Set the cursor position callback.
     *
     */
    void SetCursorPositionCallback();

    // TODO: Maybe create a camera controller class.

    /**
     * @brief Update the camera mode accordingly
     *
     */
    void UpdateCameraMode();

    /**
     * @brief Call functions required to update the camera position based on the modes.
     *
     */
    void UpdateCameraPosition();
};