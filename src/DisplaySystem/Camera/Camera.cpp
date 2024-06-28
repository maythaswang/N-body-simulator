#include <Camera.h>
#include <iostream>

Camera::Camera()
{
    this->eye = glm::vec3(0, 0, 5.0);
    this->center = glm::vec3(0, 0, 0);
    this->up = glm::vec3(0, 1.0, 0);

    this->fovy = 90;
    this->aspectW = 640;
    this->aspectH = 480;
    this->zNear = 0.1;
    this->zFar = 99.0;

    this->rotationSensitivity = 0.9;
    this->zoomSensitivity = 0.01;
    this->translationSensitivity = 0.05;

    BuildModelMat();
    BuildViewMat();
    BuildProjectionMat();
}

void Camera::Rotate(GLfloat mouseDeltaX, GLfloat mouseDeltaY)
{
    glm::vec3 direction = glm::normalize(this->center - this->eye);
    glm::vec3 right = glm::normalize(glm::cross(direction, this->up));
    GLfloat yaw = -mouseDeltaX * rotationSensitivity;  // along up-axis
    GLfloat pitch = mouseDeltaY * rotationSensitivity; // along right-axis
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
    this->BuildViewMat();
}

void Camera::Zoom(GLfloat mouseDeltaY)
{
    glm::vec3 direction = glm::normalize(this->center - this->eye);
    GLfloat zoom_power = -mouseDeltaY * zoomSensitivity;
    GLfloat zoom_limit = 0.005;

    // Set zoom limit
    glm::vec3 new_eye = this->eye + direction*zoom_power;
    glm::vec3 dtc = new_eye - this->center; // distance to center
    if ((dtc[0] > zoom_limit || dtc[0] < -zoom_limit)   | (dtc[1] > zoom_limit || dtc[1] < -zoom_limit  )|( dtc[2] > zoom_limit || dtc[2] < -zoom_limit)){
        this->eye = new_eye;
        this->BuildViewMat();
    }
    
}

void Camera::Translate(GLfloat mouseDeltaX, GLfloat mouseDeltaY)
{
    glm::vec3 direction = glm::normalize(this->center - this->eye);
    glm::vec3 right = glm::normalize(glm::cross(direction, this->up));

    GLfloat x_translate = -mouseDeltaX * translationSensitivity;
    GLfloat y_translate = mouseDeltaY * translationSensitivity;
    glm::vec3 translation_vector = glm::normalize(right) * x_translate + glm::normalize(this->up) * y_translate;

    this->eye += translation_vector;
    this->center += translation_vector;
    this->BuildViewMat();
}   

// The only mutator method avaliable for use as of now is SetAspect.

void Camera::SetEye(glm::vec3 eye)
{
    this->eye = eye;
}

void Camera::SetCenter(glm::vec3 center)
{
    this->center = center;
}

void Camera::SetUp(glm::vec3 up)
{
    this->up = up;
}

void Camera::SetFovy(GLfloat fovy)
{
    this->fovy = fovy;
}

void Camera::SetAspect(GLfloat width, GLfloat height)
{
    this->aspectW = width;
    this->aspectH = height;
    this->BuildProjectionMat();
}

void Camera::SetZnear(GLfloat zNear)
{
    this->zNear = zNear;
}

void Camera::SetZfar(GLfloat zFar)
{
    this->zFar = zFar;
}

glm::mat4 Camera::GetModelMat()
{
    return this->modelMat;
}

glm::mat4 Camera::GetViewMat()
{
    return this->viewMat;
}

glm::mat4 Camera::GetProjectionMat()
{
    return this->projectionMat;
}

void Camera::BuildModelMat()
{
    this->modelMat = glm::mat4(1.0f);
}

void Camera::BuildViewMat()
{
    this->viewMat = glm::lookAt(this->eye, this->center, this->up);
}

void Camera::BuildProjectionMat()
{
    this->projectionMat = glm::perspective(glm::radians(this->fovy), this->aspectW / this->aspectH, this->zNear, this->zFar);
}