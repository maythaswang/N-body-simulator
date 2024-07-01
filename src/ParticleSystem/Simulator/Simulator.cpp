#include <Simulator.h>

Simulator::Simulator(GLfloat gravitational_constat, GLfloat softening_factor)
{
    this->gravitational_constant = gravitational_constant;
    this->softening_factor = softening_factor;
}

glm::vec3 Simulator::calculate_force(Particle current, Particle other)
{
    // At this stage we will not multiply current mass and gravitational constant.
    glm::vec3 temp_distance = current.get_position() - other.get_position();
    glm::vec3 direction = -glm::normalize(temp_distance);

    GLfloat sq_distance = glm::dot(temp_distance, temp_distance);
    GLfloat sq_soften = std::pow(this->softening_factor, 2);

    return other.get_mass() / std::sqrt(sq_distance + sq_soften) * direction;
}