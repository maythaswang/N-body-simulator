#include <Simulator.h>

Simulator::Simulator(GLfloat n_particle, GLfloat gravitational_constat, GLfloat softening_factor, GLfloat timestep_size)
{
    this->gravitational_constant = gravitational_constant;
    this->softening_factor = softening_factor;
    this->timestep_size = timestep_size;
    this->current_time = 0;
    this->n_particle = n_particle;
}

glm::vec3 Simulator::calculate_acceleration(Particle current, Particle other)
{
    // At this stage we will not multiply current mass and gravitational constant.
    glm::vec3 temp_distance = current.get_position() - other.get_position();
    glm::vec3 direction = -glm::normalize(temp_distance);

    GLfloat sq_distance = glm::dot(temp_distance, temp_distance);
    GLfloat sq_soften = std::pow(this->softening_factor, 2);

    return other.get_mass() / std::sqrt(sq_distance + sq_soften) * direction;
}

void Simulator::next_step()
{
    this->update_position_euler();
}

void Simulator::update_position_euler()
{
    glm::vec3 tmp_acceleration;
    for (int i = 0; i < this->n_particle; i++)
    {
        for (int j = i; j < this->n_particle; j++)
        {
            tmp_acceleration = this->calculate_acceleration(particle[i], particle[j]);

            // Update Velocity
            particle[i].set_velocity(particle[i].get_velocity() + tmp_acceleration * this->timestep_size);
            particle[j].set_velocity(particle[j].get_velocity() - tmp_acceleration * this->timestep_size);

            // Update Position
            particle[i].set_position(particle[i].get_position() + particle[i].get_velocity() * this->timestep_size);
            particle[j].set_position(particle[j].get_position() + particle[i].get_velocity() * this->timestep_size);
        }
    }
}