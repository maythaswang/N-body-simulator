#include <iostream>
#include <CallbackManager.h>

CallbackManager::CallbackManager(GLFWwindow *window, Camera *camera)
{
    this->window = window;
    this->camera = camera;
    this->camera_mode = CAMERA_IDLE;

    // TODO: Maybe make a map or array to handle mouse/keyboard state.
    this->middle_mouse_down = false;
    this->left_shift_down = false;
    this->left_ctrl_down = false;

    // Set callbacks
    this->set_window_resize_callback();
    this->set_cursor_position_callback();
};

void CallbackManager::process_input()
{
    if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    this->left_ctrl_down = glfwGetKey(this->window, GLFW_KEY_LEFT_CONTROL);
    this->left_shift_down = glfwGetKey(this->window, GLFW_KEY_LEFT_SHIFT);
    this->middle_mouse_down = glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_MIDDLE);

    this->handle_input();
}

void CallbackManager::handle_input()
{
    this->update_camera_mode();
    this->update_camera_position();
}

void CallbackManager::update_camera_mode()
{
    if (!this->middle_mouse_down)
    {
        this->camera_mode = CAMERA_IDLE;
        this->old_mouse_pos_x = this->mouse_pos_x;
        this->old_mouse_pos_y = this->mouse_pos_y;
    }

    if (this->camera_mode == CAMERA_IDLE)
    {
        if (this->left_ctrl_down & this->middle_mouse_down)
        {
            this->camera_mode = CAMERA_ZOOM;
        }
        else if (this->left_shift_down & this->middle_mouse_down)
        {
            this->camera_mode = CAMERA_TRANSLATE;
        }
        else if (this->middle_mouse_down)
        {
            this->camera_mode = CAMERA_ROTATE;
        }
    }
}

void CallbackManager::update_camera_position()
{
    double delta_mouse_pos_x = this->mouse_pos_x - this->old_mouse_pos_x;
    double delta_mouse_pos_y = this->mouse_pos_y - this->old_mouse_pos_y;

    switch (this->camera_mode)
    {
    case CAMERA_IDLE:
        break;
    case CAMERA_ZOOM:
        this->camera->zoom(delta_mouse_pos_y);
        break;
    case CAMERA_ROTATE:
        camera->rotate(delta_mouse_pos_x, delta_mouse_pos_y);
        break;
    case CAMERA_TRANSLATE:
        camera->translate(delta_mouse_pos_x, delta_mouse_pos_y);
        break;
    default:
        break;
    }

    this->old_mouse_pos_x = mouse_pos_x;
    this->old_mouse_pos_y = mouse_pos_y;
}

void CallbackManager::set_cursor_position_callback()
{
    glfwSetWindowUserPointer(this->window, reinterpret_cast<void *>(this));

    glfwSetCursorPosCallback(this->window, [](GLFWwindow *window, double posX, double posY)
                             {
        CallbackManager *callback_manager = reinterpret_cast<CallbackManager *>(glfwGetWindowUserPointer(window));
        if (callback_manager)
        {
            callback_manager->mouse_pos_x = posX;
            callback_manager->mouse_pos_y = posY;
        } });
}

void CallbackManager::set_window_resize_callback()
{
    glfwSetWindowUserPointer(this->window, reinterpret_cast<void *>(this));

    // set to call this lambda function everytime the screen gets resized
    // This can be made as a normal function if it was a static function.
    glfwSetFramebufferSizeCallback(this->window, [](GLFWwindow *window, int width, int height)
                                   { 
        
        // Set the camera aspect ratio
        CallbackManager * callback_manager = reinterpret_cast<CallbackManager *> ( glfwGetWindowUserPointer ( window ));
        if (callback_manager) callback_manager->camera->set_aspect( width, height );

        // set the viewport size
        glViewport(0, 0, width, height); });
}