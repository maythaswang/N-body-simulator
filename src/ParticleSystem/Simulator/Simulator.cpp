#include <Simulator.h>

Simulator::Simulator(GLfloat n_particle, GLfloat gravitational_constant, GLfloat softening_factor, GLfloat timestep_size)
{
    this->gravitational_constant = gravitational_constant;
    this->softening_factor = softening_factor;
    this->timestep_size = timestep_size;
    this->current_time = 0;
    this->n_particle = n_particle;
    this->particle_position.resize(n_particle);
    this->particle_velocity.resize(n_particle);
    this->particle_mass.resize(n_particle);
}

glm::vec3 Simulator::calculate_acceleration(uint32_t current, uint32_t other)
{
    // At this stage we will not multiply current mass and gravitational constant.
    glm::vec3 temp_distance = this->particle_position[current] - this->particle_position[other];
    glm::vec3 direction = -glm::normalize(temp_distance);

    GLfloat sq_distance = glm::dot(temp_distance, temp_distance);
    GLfloat sq_soften = std::pow(this->softening_factor, 2);

    return this->particle_mass[other] / std::sqrt(sq_distance + sq_soften) * direction;
}

void Simulator::next_step()
{
    this->update_position_euler();
    // glBindBuffer(GL_ARRAY_BUFFER, *VBO);

}

void Simulator::update_position_euler()
{
    glm::vec3 tmp_acceleration;
    for (int i = 0; i < this->n_particle; i++)
    {
        for (int j = i; j < this->n_particle; j++)
        {
            tmp_acceleration = this->calculate_acceleration(i, j);

            // Update Velocity
            this->particle_velocity[i] += tmp_acceleration * this->timestep_size;
            this->particle_velocity[j] -= tmp_acceleration * this->timestep_size;

            // Update Position
            this->particle_position[i] += this->particle_velocity[i] * this->timestep_size;
            this->particle_position[j] += this->particle_velocity[j] * this->timestep_size;
        }
    }
}

void Simulator::initialize_particles(GLuint *VAO, GLuint *VBO)
{
    this->spawn_globular_cluster(1000);

    glGenVertexArrays(1, VAO);
    glGenBuffers(1, VBO);

    glBindVertexArray(*VAO);
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * this->n_particle * 3, &this->particle_position[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
}

void Simulator::spawn_globular_cluster(GLfloat radius)
{
    for (int i = 0; i < this->n_particle; i++)
    {
        // TODO: Increase the density near the center of the cluster.
        glm::vec3 tmp_position = glm::sphericalRand(radius);
        glm::vec3 tmp_velocity = glm::vec3(0.0f); // TODO: Maybe make it possible to select a range of initial velocity.
        GLfloat tmp_mass = 15;                    // TODO: Fix this, Let this be the uniform mass for now

        particle_position[i] = tmp_position;
        particle_velocity[i] = tmp_velocity;
        particle_mass[i] = tmp_mass;
    }
}