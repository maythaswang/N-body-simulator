#pragma once
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
private:
    glm::vec3 eye; 
    glm::vec3 center; 
    glm::vec3 up;
};