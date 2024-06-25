#include <Camera.h>
Camera::Camera()
{
    this->eye = glm::vec3(0, 0, 5.0);
    this->center = glm::vec3(0, 0, 0);
    this->up = glm::vec3(0, 1.0, 0);

    this->fovy = 90;
    this->aspectW = 500; // TODO: Get the display's width and height.
    this->aspectH = 500;
    this->zNear = 0.1;
    this->zFar = 99.0;

    buildModelMat();
    buildViewMat();
    buildProjectionMat();
}

void Camera::setEye(glm::vec3 eye)
{
    this->eye = eye;
}

void Camera::setCenter(glm::vec3 center)
{
    this->center = center;
}

void Camera::setUp(glm::vec3 up)
{
    this->up = up;
}

void Camera::setFovy(GLfloat fovy)
{
    this->fovy = fovy;
}

void Camera::setAspect(GLfloat width, GLfloat height)
{
    this->aspectW = aspectW;
    this->aspectH = aspectH;
}

void Camera::setZnear(GLfloat zNear)
{
    this->zNear = zNear;
}

void Camera::setZfar(GLfloat)
{
    this->zFar = zFar;
}

glm::mat4 Camera::getModelMat()
{
    return this->modelMat;
}

glm::mat4 Camera::getViewMat()
{
    return this->viewMat;
}

glm::mat4 Camera::getProjectionMat()
{
    return this->projectionMat;
}

void Camera::buildModelMat()
{
    this->modelMat = glm::mat4(1.0f);
}

void Camera::buildViewMat()
{
    this->viewMat = glm::lookAt(this->eye, this->center, this->up);
}

void Camera::buildProjectionMat()
{
    this->projectionMat = glm::perspective(glm::radians(this->fovy), this->aspectH / this->aspectW, this->zNear, this->zFar);
}