#ifndef CAMERA_H
#define CAMERA_H
#pragma once

#include <GLCommon.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

/**
 * @brief Stores position of camera, handle camera transformations, and construct matrix to transform polygons accordingly.
 *
 */
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
    void zoom(GLfloat);

    /**
     * @brief Rotate camera based on mouse drag.
     * 
     * @param mouse_delta_x change in x position of mouse
     * @param mouse_delta_y change in y position of mouse
     */
    void rotate(GLfloat, GLfloat);

    /**
     * @brief Translate the camera based on mouse drag.
     * @note The translation is done in the direction of up and right only.
     */
    void translate(GLfloat, GLfloat);

    /**
     * @brief Moves the eye and center forward based on mouse drag.
     *
     * @param mouse_delta_y change in y position of mouse
     */
    void free_forward(GLfloat);

    /**
     * @brief rotate all 3 components of mvp matrix
     *
     * @param mouse_delta_x change in x position of mouse
     * @param mouse_delta_y change in y position of mouse
     */
    void free_rotate(GLfloat mouse_delta_x, GLfloat mouse_delta_y);

    /**
     * @brief Set eye value
     *
     * @param eye vector of eye position
     */
    void set_eye(glm::vec3);

    /**
     * @brief Set center value
     *
     * @param center vector of center position
     */
    void set_center(glm::vec3);

    /**
     * @brief Set up value
     *
     * @param up vector of up position
     */
    void set_up(glm::vec3);

    /**
     * @brief Set fovy value
     *
     * @param fovy field of view y 
     */
    void set_fovy(GLfloat);

    /**
     * @brief Set height and width value for calculating the aspect ratio.
     *
     * @param height 
     * @param width
     */
    void set_aspect(GLfloat, GLfloat);

    /**
     * @brief Set zNear value
     *
     * @param zNear
     */
    void set_z_near(GLfloat);

    /**
     * @brief Set zFar value
     *
     * @param zFar
     */
    void set_z_far(GLfloat);

    /**
     * @brief Get the Model Matrix
     *
     * @return Model Matrix
     */
    glm::mat4 get_model_matrix();

    /**
     * @brief Get the View Matrix
     *
     * @return View Matrix
     */
    glm::mat4 get_view_matrix();

    /**
     * @brief Get the Projection Matrix
     *
     * @return Projection Matrix
     */
    glm::mat4 get_projection_matrix();

    /**
     * @brief Set the camera settings to default values
     * 
     */
    void set_default_camera();

    GLfloat get_aspect_w();
    GLfloat get_aspect_h();

private:
    glm::vec3 eye;
    glm::vec3 center;
    glm::vec3 up;

    GLfloat fovy;
    GLfloat aspect_w;
    GLfloat aspect_h;
    GLfloat z_near;
    GLfloat z_far;

    glm::mat4 model_mat;
    glm::mat4 view_mat;
    glm::mat4 projection_mat;

    GLfloat rotation_sensitivity;
    GLfloat translation_sensitivity;
    GLfloat zoom_sensitivity;

    /**
     * @brief Build model matrix.
     *
     * @return Model Matrix
     */
    void build_model_matrix();

    /**
     * @brief Build view matrix based on (eye, center, up) that has been previously stored.
     *
     * @return View Matrix
     */
    void build_view_matrix();

    /**
     * @brief Build projection matrix based on (fovy, aspectW, aspectH, zNear, zFar) that has been previously stored.
     *
     * @return Projection Matrix
     */
    void build_projection_matrix();
};
#endif