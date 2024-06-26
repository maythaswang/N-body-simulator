#pragma once
#ifndef camera_h
#define camera_h

#include <GLCommon.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Camera
{
public:
    /**
     * @brief Construct a new Camera object
     *
     */
    Camera();

    /**
     * @brief Zoom In-Out based on mouse drag.
     * @param newY y position in reference to the original point
     */
    void Zoom(GLfloat);

    /**
     * @brief Rotate camera based on mouse drag.
     * @param 
     * @param
     * 
     */
    void Rotate(GLfloat, GLfloat);

    /**
     * @brief Translate the camera based on mouse drag.
     * @note The translation is done in the direction of up and right only.
     */
    void Translate(GLfloat, GLfloat);

    /**
     * @brief Set eye value
     *
     * @param eye vector of eye position
     */
    void SetEye(glm::vec3);

    /**
     * @brief Set center value
     *
     * @param center vector of center position
     */
    void SetCenter(glm::vec3);

    /**
     * @brief Set up value
     *
     * @param up vector of up position
     */
    void SetUp(glm::vec3);

    /**
     * @brief Set fovy value
     *
     * @param fovy
     */
    void SetFovy(GLfloat);

    /**
     * @brief Set height and width value for calculating the aspect ratio.
     *
     * @param height
     * @param width
     */
    void SetAspect(GLfloat, GLfloat);

    /**
     * @brief Set zNear value
     *
     * @param zNear
     */
    void SetZnear(GLfloat);

    /**
     * @brief Set zFar value
     *
     * @param zFar
     */
    void SetZfar(GLfloat);

    /**
     * @brief Get the Model Matrix
     *
     * @return Model Matrix
     */
    glm::mat4 GetModelMat();

    /**
     * @brief Get the View Matrix
     *
     * @return View Matrix
     */
    glm::mat4 GetViewMat();

    /**
     * @brief Get the Projection Matrix
     *
     * @return Projection Matrix
     */
    glm::mat4 GetProjectionMat();

private:
    glm::vec3 eye;
    glm::vec3 center;
    glm::vec3 up;

    GLfloat fovy;
    GLfloat aspectW;
    GLfloat aspectH;
    GLfloat zNear;
    GLfloat zFar;

    glm::mat4 modelMat;
    glm::mat4 viewMat;
    glm::mat4 projectionMat;

    GLfloat rotationSensitivity;
    GLfloat translationSensitivity;
    GLfloat zoomSensitivity;

    /**
     * @brief Build model matrix.
     *
     * @return Model Matrix
     */
    void BuildModelMat();

    /**
     * @brief Build view matrix based on (eye, center, up) that has been previously stored.
     *
     * @return View Matrix
     */
    void BuildViewMat();

    /**
     * @brief Build projection matrix based on (fovy, aspectW, aspectH, zNear, zFar) that has been previously stored.
     *
     * @return Projection Matrix
     */
    void BuildProjectionMat();
};
#endif