#include <iostream>
#include <CallbackManager.h>

CallbackManager::CallbackManager(GLFWwindow *window, Camera *camera)
{
    this->window = window;
    this->camera = camera;
    this->cameraMode = CAMERA_IDLE;

    // TODO: Maybe make a map or array to handle mouse/keyboard state.
    // Personal note: GLFW_PRESS: 1, GLFW_RELEASE: 0

    this->middleMouseDown = false;
    this->leftShiftDown = false;
    this->leftCtrlDown = false;

    // Set callbacks
    this->SetWindowResizeCallback();
    this->SetCursorPositionCallback();
};

void CallbackManager::ProcessInput()
{
    if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    leftCtrlDown = glfwGetKey(this->window, GLFW_KEY_LEFT_CONTROL);
    leftShiftDown = glfwGetKey(this->window, GLFW_KEY_LEFT_SHIFT);
    middleMouseDown = glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_MIDDLE);

    this->HandleInput();
}

void CallbackManager::HandleInput()
{
    this->UpdateCameraMode();
    this->UpdateCameraPosition();
}

void CallbackManager::UpdateCameraMode()
{
    if (!middleMouseDown)
    {
        this->cameraMode = CAMERA_IDLE;
        this->old_mouse_pos_x = this->mousePosX;
        this->old_mouse_pos_y = this->mousePosY;
    }

    if (this->cameraMode == CAMERA_IDLE & middleMouseDown)
    {
        if (leftCtrlDown)
        {
            this->cameraMode = CAMERA_ZOOM;
        }
        else if (leftShiftDown)
        {
            this->cameraMode = CAMERA_TRANSLATE;
        }
        else
        {
            this->cameraMode = CAMERA_ROTATE;
        }
    }
}

void CallbackManager::UpdateCameraPosition()
{
    double delta_mouse_pos_x = this->mousePosX - this->old_mouse_pos_x;
    double delta_mouse_pos_y = this->mousePosY - this->old_mouse_pos_y;

    // std::cout << delta_mouse_pos_x << ' ' << delta_mouse_pos_y << std::endl;

    switch (this->cameraMode)
    {
    case CAMERA_IDLE:
        break;
    case CAMERA_ZOOM:
        break;
    case CAMERA_ROTATE:
        camera->Rotate( (GLfloat)delta_mouse_pos_x,(GLfloat) delta_mouse_pos_y);
        break;
    case CAMERA_TRANSLATE:
        break;
    default:
        break;
    }

    this->old_mouse_pos_x = mousePosX;
    this->old_mouse_pos_y = mousePosY;
}

void CallbackManager::SetCursorPositionCallback()
{
    glfwSetWindowUserPointer(this->window, reinterpret_cast<void *>(this));

    glfwSetCursorPosCallback(this->window, [](GLFWwindow *window, double posX, double posY)
                             {
        CallbackManager *callback_manager = reinterpret_cast<CallbackManager *>(glfwGetWindowUserPointer(window));
        if (callback_manager)
        {
            callback_manager->mousePosX = posX;
            callback_manager->mousePosY = posY;
        } });
}

void CallbackManager::SetWindowResizeCallback()
{
    glfwSetWindowUserPointer(this->window, reinterpret_cast<void *>(this));

    // set to call this lambda function everytime the screen gets resized
    // This can be made as a normal function if it was a static function.
    glfwSetFramebufferSizeCallback(this->window, [](GLFWwindow *window, int width, int height)
                                   { 
        
        // Set the camera aspect ratio
        CallbackManager * callback_manager = reinterpret_cast<CallbackManager *> ( glfwGetWindowUserPointer ( window ));
        if (callback_manager) callback_manager->camera->SetAspect( width, height );

        // set the viewport size
        glViewport(0, 0, width, height); });
}