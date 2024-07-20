#include <iostream>
#include <StringCommon.h>
#include <CallbackManager.h>

CallbackManager::CallbackManager(GLFWwindow *window, Camera *camera, Simulator *simulator)
{
    this->window = window;
    this->camera = camera;
    this->simulator = simulator;
    this->camera_mode = CAMERA_IDLE;
    this->camera_orbiting = true;

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
        if (this->camera_orbiting)
        {
            this->camera->zoom(delta_mouse_pos_y);
        }
        else
        {
            this->camera->free_forward(delta_mouse_pos_y);
        }

        break;
    case CAMERA_ROTATE:
        if (this->camera_orbiting)
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

void CallbackManager::set_camera_orbiting(bool camera_orbiting)
{
    this->camera_orbiting = camera_orbiting;
}
bool CallbackManager::get_camera_orbiting()
{
    return this->camera_orbiting;
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

void CallbackManager::set_keyboard_callback()
{
    glfwSetWindowUserPointer(this->window, reinterpret_cast<void *>(this));

    glfwSetKeyCallback(this->window, [](GLFWwindow *window, int key, int scancode, int action, int mods)
                       {
        CallbackManager * callback_manager = reinterpret_cast<CallbackManager *> ( glfwGetWindowUserPointer ( window ));
        if (callback_manager){
            if (key == GLFW_KEY_P && action == GLFW_PRESS)
            {   
                GLuint current_step = callback_manager->simulator->get_current_step();
                GLfloat timestep_size = callback_manager->simulator->get_timestep_size();
                if(callback_manager->simulator->get_running_state())
                {
                    std::cout << "The simulation is now paused. Step: " << current_step << ", Time (timestep size): " 
                    << current_step * timestep_size << "\nPress p to resume..." << std::endl;
                } 
                else 
                {
                    std::cout << "Resuming simulation..." << std::endl;
                }


                callback_manager->simulator->set_running_state(!callback_manager->simulator->get_running_state());
            } 

            if (key == GLFW_KEY_H && action == GLFW_PRESS)
            {
                std::cout << g_controls_help << std::endl;
            }

            if (key == GLFW_KEY_I && action == GLFW_PRESS){
                std::cout << callback_manager->simulator->get_setup_log()<< std::endl;
            }
            
            if (key == GLFW_KEY_O && action == GLFW_PRESS){
                bool is_orbiting = callback_manager->get_camera_orbiting();
                callback_manager->set_camera_orbiting(!is_orbiting);

                // This one checks the previous state and do the inverse 
                std::string msg = (is_orbiting) ? "Camera is set to free flying mode." : "Camera is set to orbit mode.";
                std::cout << msg << std::endl;
            }

        } });
}

void CallbackManager::set_scroll_callback()
{
    glfwSetWindowUserPointer(this->window, reinterpret_cast<void *>(this));

    glfwSetScrollCallback(this->window, [](GLFWwindow *window, double x_offset, double y_offset)
                          {
        CallbackManager * callback_manager = reinterpret_cast<CallbackManager *> ( glfwGetWindowUserPointer ( window ));
        if (callback_manager){
            if(callback_manager->camera_mode == CAMERA_IDLE)
            {
                if(callback_manager->camera_orbiting)
                {
                    callback_manager->camera->zoom(-y_offset*1000);
                }
                else 
                {
                    callback_manager->camera->free_forward(-y_offset * 1000);
                }
            }
        } });
}