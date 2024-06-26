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

    BuildModelMat();
    BuildViewMat();
    BuildProjectionMat();
}

void Camera::Rotate(GLfloat mouseDeltaX, GLfloat mouseDeltaY)
{
    glm::vec3 right = glm::normalize(glm::cross(this->eye, this->up));
    GLfloat yaw = -mouseDeltaX * rotationSensitivity;  // along up-axis
    GLfloat pitch = mouseDeltaY * rotationSensitivity; // along right-axis
    // roll: along the center-axis

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::mat4 rotationYaw = glm::rotate(glm::mat4(1.0f), glm::radians(yaw), this->up); // TODO: Maybe have to change this up later.
    glm::mat4 rotationPitch = glm::rotate(rotationYaw, glm::radians(pitch), right);    // TODO: Maybe have to change this up later.

    glm::mat3 rotation = glm::mat3(rotationPitch * rotationYaw);
    
    this->eye = rotation * this->eye;
    this->up = rotation * this->up;
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

void Camera::SetZfar(GLfloat)
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