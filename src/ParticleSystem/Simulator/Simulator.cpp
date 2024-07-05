#include <Simulator.h>
#include <iostream>

// TODO: Create Enumerator for Swapping Integrator midway (Make sure this can only happen during paused state.)

Simulator::Simulator(GLfloat n_particle, GLfloat gravitational_constant, GLfloat softening_factor, GLfloat timestep_size)
{
    this->gravitational_constant = gravitational_constant;
    this->softening_factor = softening_factor;
    this->timestep_size = timestep_size;
    this->current_step = 0;
    this->running_state = 0;

    this->n_particle = n_particle;
    this->particle_position.resize(n_particle);
    this->particle_velocity.resize(n_particle);
    this->particle_mass.resize(n_particle);
    this->particle_acceleration.resize(n_particle);
}

glm::vec3 Simulator::calculate_acceleration(uint32_t current, uint32_t other)
{
    // At this stage we will not multiply current mass and gravitational constant.
    glm::vec3 temp_distance = this->particle_position[current] - this->particle_position[other];
    glm::vec3 direction = -glm::normalize(temp_distance);
    GLfloat sq_distance = glm::dot(temp_distance, temp_distance);
    GLfloat sq_soften = std::pow(this->softening_factor, 2);
    return (this->particle_mass[other] / std::sqrt(sq_distance + sq_soften)) * direction;
}

void Simulator::next_step()
{
    this->update_position_euler();
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * this->n_particle * 3, &this->particle_position[0]);

    this->current_step +=1;
}

void Simulator::update_position_euler()
{
    glm::vec3 tmp_acceleration;
    std::fill(this->particle_acceleration.begin(), this->particle_acceleration.end(), glm::vec3(0.0f));

    for (int i = 0; i < this->n_particle; i++)
    {
        for (int j = i + 1; j < this->n_particle; j++)
        {
            tmp_acceleration = this->calculate_acceleration(i, j);
            this->particle_acceleration[i] += tmp_acceleration;
            this->particle_acceleration[j] -= tmp_acceleration;
        }
        // Update Velocity

        this->particle_velocity[i] += this->particle_acceleration[i] * this->timestep_size * this->gravitational_constant;

        // Update Position
        this->particle_position[i] += this->particle_velocity[i] * this->timestep_size;
    }
}

void Simulator::initialize_particles(GLuint *VAO, GLuint *VBO)
{
    this->spawn_globular_cluster(500, 100, 100000);
    // this->spawn_sphere(500,100, 100000);

    glGenVertexArrays(1, VAO);
    glGenBuffers(1, VBO);

    glBindVertexArray(*VAO);
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * this->n_particle * 3, &this->particle_position[0], GL_STREAM_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    this->VAO = VAO;
    this->VBO = VBO;
}

// TODO: Accept min,max velocity as input
void Simulator::spawn_globular_cluster(GLfloat radius, GLfloat min_mass, GLfloat max_mass)
{
    GLfloat tmp_radius = radius;
    for (int i = 0; i < this->n_particle; i++)
    {
        glm::vec3 tmp_position = glm::sphericalRand(tmp_radius * glm::linearRand(0.0f, 1.0f) + 25); // This will ensure that at least the center will be a bit more dense. (use integer and it will spawn right in the middle)
        glm::vec3 tmp_velocity = glm::vec3(0.0f);                                                   // TODO: Maybe make it possible to select a range of initial velocity.
        GLfloat tmp_mass = glm::linearRand(min_mass, max_mass);
        particle_position[i] = tmp_position;
        particle_velocity[i] = tmp_velocity;
        particle_mass[i] = tmp_mass;
    }
}

void Simulator::spawn_sphere(GLfloat radius, GLfloat min_mass, GLfloat max_mass)
{
    for (int i = 0; i < this->n_particle; i++)
    {
        glm::vec3 tmp_position = glm::sphericalRand(radius);
        glm::vec3 tmp_velocity = glm::vec3(0.0f); // TODO: Maybe make it possible to select a range of initial velocity.
        GLfloat tmp_mass = glm::linearRand(min_mass, max_mass);
        particle_position[i] = tmp_position;
        particle_velocity[i] = tmp_velocity;
        particle_mass[i] = tmp_mass;
    }
}

bool Simulator::get_running_state()
{
    return this->running_state;
}
void Simulator::set_running_state(bool running_state)
{
    this->running_state = running_state;
}

GLuint Simulator::get_current_step(){
    return this->current_step;
}

GLfloat Simulator::get_timestep_size(){
    return this->timestep_size;
}