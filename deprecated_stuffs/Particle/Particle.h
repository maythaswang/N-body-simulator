#pragma once
#include <GLcommon.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Particle
{
public:
    Particle();
    Particle(glm::vec3 position, glm::vec3 velocity, GLfloat mass);
    void print_information();

    GLfloat get_mass();
    glm::vec3 get_position();
    glm::vec3 get_velocity();
    glm::vec3 get_acceleration();

    void set_position(glm::vec3);
    void set_mass(GLfloat);
    void set_velocity(glm::vec3);
    void set_acceleration(glm::vec3);

private:
    GLfloat mass;
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;
};