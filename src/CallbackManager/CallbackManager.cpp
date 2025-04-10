#include <iostream>
#include <StringCommon.h>
#include "CallbackManager.h"

CallbackManager::CallbackManager(GLFWwindow *window, Camera *camera, InputProcessor *input_processor, Bloom *bloom)
{
    // Components
    this->window = window;
    this->camera = camera;
    this->input_processor = input_processor;
    this->bloom = bloom;

    // Mouse states
    this->middle_mouse_down = false;
    this->left_shift_down = false;
    this->left_ctrl_down = false;

    // Set callbacks
    this->set_window_resize_callback();
    this->set_cursor_position_callback();
    this->set_keyboard_callback();
    this->set_scroll_callback();
};

void CallbackManager::process_input()
{
    if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // We check everyframe and not as event.
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
        this->camera->set_camera_mode(CAMERA_IDLE);
        this->old_mouse_pos_x = this->mouse_pos_x;
        this->old_mouse_pos_y = this->mouse_pos_y;
    }
    else if (this->camera->get_camera_mode() == CAMERA_IDLE & this->middle_mouse_down)
    {
        if (this->left_ctrl_down)
        {
            this->camera->set_camera_mode(CAMERA_ZOOM);
        }
        else if (this->left_shift_down)
        {
            this->camera->set_camera_mode(CAMERA_TRANSLATE);
        }
        else
        {
            this->camera->set_camera_mode(CAMERA_ROTATE);
        }
    }
}

void CallbackManager::update_camera_position()
{
    double delta_mouse_pos_x = this->mouse_pos_x - this->old_mouse_pos_x;
    double delta_mouse_pos_y = this->mouse_pos_y - this->old_mouse_pos_y;

    switch (this->camera->get_camera_mode())
    {
    case CAMERA_IDLE:
        break;
    case CAMERA_ZOOM:
        if (this->camera->get_is_orbiting())
        {
            this->camera->zoom(delta_mouse_pos_y);
        }
        else
        {
            this->camera->free_forward(delta_mouse_pos_y);
        }

        break;
    case CAMERA_ROTATE:
        if (this->camera->get_is_orbiting())
        {

            this->camera->rotate(delta_mouse_pos_x, delta_mouse_pos_y);
        }
        else
        {
            this->camera->free_rotate(delta_mouse_pos_x, delta_mouse_pos_y);
        }

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

        if (callback_manager){
            if(width || height) {
            callback_manager->camera->set_aspect( width, height );
            callback_manager->bloom->resize(width, height);
            }
        }

        // set the viewport size
        glViewport(0, 0, width, height); });
}

void CallbackManager::set_scroll_callback()
{
    glfwSetWindowUserPointer(this->window, reinterpret_cast<void *>(this));

    glfwSetScrollCallback(this->window, [](GLFWwindow *window, double x_offset, double y_offset)
                          {
        CallbackManager * callback_manager = reinterpret_cast<CallbackManager *> ( glfwGetWindowUserPointer ( window ));
        if (callback_manager){
            // Hard Zoom
            if(callback_manager->camera->get_camera_mode() == CAMERA_IDLE)
            {
                if(callback_manager->camera->get_is_orbiting())
                {
                    callback_manager->camera->zoom(-y_offset * 1000);
                }
                else 
                {
                    callback_manager->camera->free_forward(-y_offset * 1000);
                }
            }
        } });
}

void CallbackManager::set_keyboard_callback()
{
    glfwSetWindowUserPointer(this->window, reinterpret_cast<void *>(this));

    glfwSetKeyCallback(this->window, [](GLFWwindow *window, int key, int scancode, int action, int mods)
                       {
        CallbackManager * callback_manager = reinterpret_cast<CallbackManager *> ( glfwGetWindowUserPointer ( window ));
        if (callback_manager && action == GLFW_PRESS){
            switch(key){
                case GLFW_KEY_P: // Pause
                    callback_manager->input_processor->imm_handle_pause();
                    break;

                case GLFW_KEY_H: // Help
                    callback_manager->input_processor->imm_handle_show_help_msg();
                    break;

                case GLFW_KEY_O: // Toggle Orbit Mode
                    callback_manager->input_processor->imm_handle_camera_orbit_toggle();
                    break;

                // TODO: Add all below this to README and the help message
                case GLFW_KEY_R: // Reset camera origin
                    callback_manager->input_processor->imm_handle_camera_reset();
                    break;

                case GLFW_KEY_K: // Toggle Instancing
                    callback_manager->input_processor->instancing_on[0] = !callback_manager->input_processor->instancing_on[0];
                    break;

                case GLFW_KEY_F: // Toggle Wireframe Mode
                    callback_manager->input_processor->wireframe_on[0] = !callback_manager->input_processor->wireframe_on[0];
                    break;

                case GLFW_KEY_B: // Toggle Bloom
                    callback_manager->input_processor->bloom_on[0] = !callback_manager->input_processor->bloom_on[0];
                    break;

                case GLFW_KEY_M: // Toggle mass-size
                    callback_manager->input_processor->msize_on[0] = !callback_manager->input_processor->msize_on[0];
                    break;
                
                case GLFW_KEY_C: // Toggle mass-color
                    callback_manager->input_processor->mcolor_on[0] = !callback_manager->input_processor->mcolor_on[0];
                    break;

                case GLFW_KEY_N: // Toggle GUI
                    callback_manager->input_processor->imm_handle_gui_toggle();
                    break;

                default: 
                    break;
            }
        } });
}