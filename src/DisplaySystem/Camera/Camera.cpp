#include <Camera.h>

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

    this->rotationSensitivity = 0.05;

    BuildModelMat();
    BuildViewMat();
    BuildProjectionMat();
}

void Camera::Rotate(double mouseDeltaX, double mouseDeltaY)
{
    glm::vec3 right = glm::normalize(glm::cross(this->eye, this->up));

    GLfloat yaw = mouseDeltaX * rotationSensitivity; // along the center-axis
    GLfloat pitch = mouseDeltaY * rotationSensitivity; // along the right-axis
    // roll: along the eye-axis direction
    
    glm::mat4 rotationYaw = glm::rotate(glm::mat4(1.0f), yaw, this->center);
    glm::mat4 rotationPitch = glm::rotate(glm::mat4(1.0f), pitch, right);
    
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