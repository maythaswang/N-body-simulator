#include <Camera.h>
#include <iostream>

Camera::Camera()
{
    this->eye = glm::vec3(0, 0, 200.0);
    this->center = glm::vec3(0, 0, 0);
    this->up = glm::vec3(0, 1.0, 0);

    this->fovy = 90;
    this->aspect_w = 640;
    this->aspect_h = 480;
    this->z_near = 0.1;
    this->z_far = 50000.0;

    this->rotation_sensitivity = 0.9;
    this->zoom_sensitivity = 1;
    this->translation_sensitivity = 0.7;

    this->build_model_matrix();
    this->build_view_matrix();
    this->build_projection_matrix();
}

void Camera::rotate(GLfloat mouse_delta_x, GLfloat mouse_delta_y)
{
    glm::vec3 direction = glm::normalize(this->center - this->eye);
    glm::vec3 right = glm::normalize(glm::cross(direction, this->up));
    GLfloat yaw = -mouse_delta_x * rotation_sensitivity;  // along up-axis
    GLfloat pitch = mouse_delta_y * rotation_sensitivity; // along right-axis
    // roll: along the center-axis

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    // Rotation Matrix
    glm::mat4 rotationYaw = glm::rotate(glm::mat4(1.0f), glm::radians(yaw), this->up);
    glm::mat4 rotationPitch = glm::rotate(rotationYaw, glm::radians(pitch), right);
    glm::mat3 rotation = glm::mat3(rotationPitch);

    this->eye = rotation * this->eye;
    this->up = rotation * this->up;
    this->build_view_matrix();
}

void Camera::zoom(GLfloat mouse_delta_y)
{
    glm::vec3 direction = glm::normalize(this->center - this->eye);
    GLfloat zoom_power = -mouse_delta_y * zoom_sensitivity;

    // Set zoom limit
    glm::vec3 new_eye = this->eye + direction * zoom_power; 

    glm::vec3 etc = this->eye - this->center;
    glm::vec3 netc = new_eye - this->center;

    bool x_in_bound = etc[0] * netc[0] > 0 || !this->eye[0];
    bool y_in_bound = etc[1] * netc[1] > 0 || !this->eye[1];
    bool z_in_bound = etc[2] * netc[2] > 0 || !this->eye[2];

    if(x_in_bound && y_in_bound && z_in_bound)
    {
        this->eye = new_eye;
        this->build_view_matrix();
    }
}

void Camera::translate(GLfloat mouse_delta_x, GLfloat mouse_delta_y)
{
    glm::vec3 direction = glm::normalize(this->center - this->eye);
    glm::vec3 right = glm::normalize(glm::cross(direction, this->up));

    GLfloat x_translate = -mouse_delta_x * this->translation_sensitivity;
    GLfloat y_translate = mouse_delta_y * this->translation_sensitivity;
    glm::vec3 translation_vector = glm::normalize(right) * x_translate + glm::normalize(this->up) * y_translate;

    this->eye += translation_vector;
    this->center += translation_vector;
    this->build_view_matrix();
}

// The only mutator method avaliable for use as of now is SetAspect.

void Camera::set_eye(glm::vec3 eye)
{
    this->eye = eye;
}

void Camera::set_center(glm::vec3 center)
{
    this->center = center;
}

void Camera::set_up(glm::vec3 up)
{
    this->up = up;
}

void Camera::set_fovy(GLfloat fovy)
{
    this->fovy = fovy;
}

void Camera::set_aspect(GLfloat width, GLfloat height)
{
    this->aspect_w = width;
    this->aspect_h = height;
    this->build_projection_matrix();
}

void Camera::set_z_near(GLfloat z_near)
{
    this->z_near = z_near;
}

void Camera::set_z_far(GLfloat z_far)
{
    this->z_far = z_far;
}

glm::mat4 Camera::get_model_matrix()
{
    return this->model_mat;
}

glm::mat4 Camera::get_view_matrix()
{
    return this->view_mat;
}

glm::mat4 Camera::get_projection_matrix()
{
    return this->projection_mat;
}

void Camera::build_model_matrix()
{
    this->model_mat = glm::mat4(1.0f);
}

void Camera::build_view_matrix()
{
    this->view_mat = glm::lookAt(this->eye, this->center, this->up);
}

void Camera::build_projection_matrix()
{
    this->projection_mat = glm::perspective(glm::radians(this->fovy), this->aspect_w / this->aspect_h, this->z_near, this->z_far);
}