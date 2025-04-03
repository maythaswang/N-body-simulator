#include <ParticleParticleCPU.h>

ParticleParticleCPU::ParticleParticleCPU(GLfloat n_particle, GLfloat gravitational_constant, GLfloat softening_factor, GLfloat timestep_size, SimulatorIntegrator integrator) : Simulator(n_particle, gravitational_constant, softening_factor, timestep_size, integrator)
{
}

glm::vec4 ParticleParticleCPU::calculate_acceleration(uint32_t current, uint32_t other)
{
    glm::vec3 temp_distance = this->particle_position[current] - this->particle_position[other];

    // Since we did not handle collision, this will prevent 0 division when calculating direction (as inaccurate as it is).
    if (temp_distance == glm::vec3(0.0f))
    {
        return glm::vec4(0.0f);
    }

    glm::vec3 direction = -glm::normalize(temp_distance);
    GLfloat sq_distance = glm::dot(temp_distance, temp_distance);
    GLfloat sq_soften = std::pow(this->softening_factor, 2);
    return glm::vec4((this->particle_mass[other] / std::sqrt(sq_distance + sq_soften)) * direction,0);
}

void ParticleParticleCPU::update_position_euler()
{
    glm::vec4 tmp_acceleration;
    std::fill(this->particle_acceleration.begin(), this->particle_acceleration.end(), glm::vec4(0.0f));

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

    this->update_SSBO();
}

void ParticleParticleCPU::update_position_velocity_verlet()
{
    glm::vec4 tmp_acceleration;
    std::fill(this->particle_acceleration.begin(), this->particle_acceleration.end(), glm::vec4(0.0f));

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

    this->update_SSBO();
}

void ParticleParticleCPU::load_particles(GLuint n, std::vector<glm::vec4> position, std::vector<glm::vec4> velocity, std::vector<glm::vec4> previous_acceleration, std::vector<GLfloat> mass)
{
    this->n_particle = n;

    // Resize vector
    this->particle_position.resize(n);
    this->particle_velocity.resize(n);
    this->particle_previous_acceleration.resize(n);
    this->particle_acceleration.resize(n);
    this->particle_mass.resize(n);

    this->particle_position = position;
    this->particle_velocity = velocity;
    this->particle_previous_acceleration = previous_acceleration;
    this->particle_mass = mass;
    this->particle_acceleration.resize(this->n_particle);
    
    this->init_SSBOs();
}

void ParticleParticleCPU::init_SSBOs()
{
    glGenBuffers(1, &this->particle_position_SSBO);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->particle_position_SSBO);
    glBufferData(GL_SHADER_STORAGE_BUFFER, this->n_particle * 4 * sizeof(GLfloat), &this->particle_position[0], GL_STREAM_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, this->particle_position_SSBO);

    glGenBuffers(1, &this->particle_mass_SSBO);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->particle_mass_SSBO);
    glBufferData(GL_SHADER_STORAGE_BUFFER, this->n_particle * 1 * sizeof(GLfloat), &this->particle_mass[0], GL_STREAM_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, this->particle_mass_SSBO);

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void ParticleParticleCPU::update_SSBO(){
    glBindBuffer(GL_ARRAY_BUFFER, this->particle_position_SSBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * this->n_particle * 4, &this->particle_position[0]);
}