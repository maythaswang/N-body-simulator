#include <ParticleParticleCPU.h>

ParticleParticleCPU::ParticleParticleCPU(GLfloat n_particle, GLfloat gravitational_constant, GLfloat softening_factor, GLfloat timestep_size, SimulatorIntegrator integrator) : Simulator(n_particle, gravitational_constant, softening_factor, timestep_size, integrator)
{
}

glm::vec3 ParticleParticleCPU::calculate_acceleration(uint32_t current, uint32_t other)
{
    glm::vec3 temp_distance = this->particle_position[current] - this->particle_position[other];

    // Since we did not handle collision, this will prevent 0 division when calculating direction (as inaccurate as it is).
    if (temp_distance == glm::vec3(0.0f))
    {
        return glm::vec3(0.0f);
    }

    glm::vec3 direction = -glm::normalize(temp_distance);
    GLfloat sq_distance = glm::dot(temp_distance, temp_distance);
    GLfloat sq_soften = std::pow(this->softening_factor, 2);
    return (this->particle_mass[other] / std::sqrt(sq_distance + sq_soften)) * direction;
}

void ParticleParticleCPU::update_position_euler()
{
    glm::vec3 tmp_acceleration;
    std::fill(this->particle_acceleration.begin(), this->particle_acceleration.end(), glm::vec3(0.0f));

    // Update Acceleration
    for (int i = 0; i < this->n_particle; i++)
    {
        for (int j = i + 1; j < this->n_particle; j++)
        {
            tmp_acceleration = this->calculate_acceleration(i, j);
            this->particle_acceleration[i] += tmp_acceleration;
            this->particle_acceleration[j] -= tmp_acceleration;
        }
    }

    for (int i = 0; i < this->n_particle; i++)
    {
        // Update Velocity
        this->particle_velocity[i] += this->particle_acceleration[i] * this->timestep_size * this->gravitational_constant;

        // Update Position
        this->particle_position[i] += this->particle_velocity[i] * this->timestep_size;
    }
}

void ParticleParticleCPU::update_position_velocity_verlet()
{
    glm::vec3 tmp_acceleration;
    std::fill(this->particle_acceleration.begin(), this->particle_acceleration.end(), glm::vec3(0.0f));

    for (int i = 0; i < this->n_particle; i++)
    {
        // Update velocity by 1/2 timestep
        this->particle_velocity[i] += this->particle_previous_acceleration[i] * this->timestep_size * (GLfloat)0.5 * this->gravitational_constant;

        // Update position by 1 step
        this->particle_position[i] += this->particle_velocity[i] * this->timestep_size;
    }

    // Update Acceleration by 1 step
    for (int i = 0; i < this->n_particle; i++)
    {
        for (int j = i + 1; j < this->n_particle; j++)
        {
            tmp_acceleration = this->calculate_acceleration(i, j);
            this->particle_acceleration[i] += tmp_acceleration;
            this->particle_acceleration[j] -= tmp_acceleration;
        }

        // Update Velocity by 1 step
        this->particle_velocity[i] += particle_acceleration[i] * this->timestep_size * (GLfloat)0.5 * this->gravitational_constant;
        
        // Store Acceleration for next step.
        this->particle_previous_acceleration[i] = this->particle_acceleration[i];
    }

    // Copy next step acceleration for next iteration
    // std::copy(this->particle_previous_acceleration.begin(), this->particle_previous_acceleration.end(), std::back_inserter(this->particle_acceleration)); // This somewhat segfaults.
}

void ParticleParticleCPU::load_particles(GLuint n, std::vector<glm::vec4> position, std::vector<glm::vec4> velocity, std::vector<glm::vec4> previous_acceleration, std::vector<GLfloat> mass)
{
    this->n_particle = n;
    this->particle_position = position;
    this->particle_velocity = velocity;
    this->particle_previous_acceleration = previous_acceleration;
    this->particle_mass = mass;
    this->particle_acceleration.resize(this->n_particle);
}