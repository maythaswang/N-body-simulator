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
     * @brief Set eye value
     *
     * @param eye vector of eye position
     */
    void setEye(glm::vec3);

    /**
     * @brief Set center value
     *
     * @param center vector of center position
     */
    void setCenter(glm::vec3);

    /**
     * @brief Set up value
     *
     * @param up vector of up position
     */
    void setUp(glm::vec3);

    /**
     * @brief Set fovy value
     *
     * @param fovy
     */
    void setFovy(GLfloat);

    /**
     * @brief Set height and width value for calculating the aspect ratio.
     *
     * @param height
     * @param width
     */
    void setAspect(GLfloat, GLfloat);

    /**
     * @brief Set zNear value
     *
     * @param zNear
     */
    void setZnear(GLfloat);

    /**
     * @brief Set zFar value
     *
     * @param zFar
     */
    void setZfar(GLfloat);

    /**
     * @brief Get the Model Matrix
     *
     * @return Model Matrix
     */
    glm::mat4 getModelMat();

    /**
     * @brief Get the View Matrix
     *
     * @return View Matrix
     */
    glm::mat4 getViewMat();

    /**
     * @brief Get the Projection Matrix
     *
     * @return Projection Matrix
     */
    glm::mat4 getProjectionMat();

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

    /**
     * @brief Build model matrix.
     *
     * @return Model Matrix
     */
    void buildModelMat();

    /**
     * @brief Build view matrix based on (eye, center, up) that has been previously stored.
     *
     * @return View Matrix
     */
    void buildViewMat();

    /**
     * @brief Build projection matrix based on (fovy, aspectW, aspectH, zNear, zFar) that has been previously stored.
     *
     * @return Projection Matrix
     */
    void buildProjectionMat();
};
#endif