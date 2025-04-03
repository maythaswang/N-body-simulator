#include <ParticleParticleGPU.h>

ParticleParticleGPU::ParticleParticleGPU(GLfloat n_particle, GLfloat gravitational_constant, GLfloat softening_factor, GLfloat timestep_size, SimulatorIntegrator integrator) : Simulator(n_particle, gravitational_constant, softening_factor, timestep_size, integrator)
{
}

void ParticleParticleGPU::next_step()
{
    this->update_position();

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->particle_position_SSBO);
    glm::vec4 *rtn = static_cast<glm::vec4 *>(glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_ONLY));
    glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
    this->update_position_vector(rtn);
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * this->n_particle * 3, &this->particle_position[0]);

    this->current_step += 1;
}

// We're going to deprecate this soon
void ParticleParticleGPU::update_position_vector(glm::vec4 *old)
{
    for (int i = 0; i < this->n_particle; i++)
    {
        this->particle_position[i] = (glm::vec4(old[i].x, old[i].y, old[i].z, 1));
    }
}

void ParticleParticleGPU::update_position()
{
    this->compute_shader_program.use();
    this->compute_shader_program.set_float("gravitational_constant", this->gravitational_constant);
    this->compute_shader_program.set_float("softening_factor", this->softening_factor);
    this->compute_shader_program.set_float("timestep_size", this->timestep_size);
    this->compute_shader_program.set_int("n_particle", this->n_particle);
    glDispatchCompute(this->n_work_groups, 1, 1);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
}

void ParticleParticleGPU::load_particles(GLuint n, std::vector<glm::vec4> position, std::vector<glm::vec4> velocity, std::vector<glm::vec4> previous_acceleration, std::vector<GLfloat> mass)
{
    this->n_particle = n;

    // Resize vector
    this->particle_position.resize(n);
    this->particle_velocity.resize(n);
    this->particle_previous_acceleration.resize(n);
    this->particle_mass.resize(n);

    // this->particle_position = position;
    std::copy(position.begin(), position.end(), this->particle_position.begin());

    std::cout << position[0].b << std::endl;
    std::copy(velocity.begin(), velocity.end(), this->particle_velocity.begin());
    std::copy(previous_acceleration.begin(), previous_acceleration.end(), this->particle_previous_acceleration.begin());
    std::copy(mass.begin(), mass.end(), this->particle_mass.begin());

    // this->particle_pos_vec4 = this->convert_to_vec4(position);
    // this->particle_vel_vec4 = this->convert_to_vec4(velocity);
    // this->particle_acc_vec4 = this->convert_to_vec4(previous_acceleration);
    // this->particle_mass = mass;

    this->n_work_groups = (GLuint)std::ceil(((GLfloat)this->n_particle) / 64);
    this->init_compute_shader();
    this->init_SSBOs();
}

// std::vector<glm::vec4> ParticleParticleGPU::convert_to_vec4(std::vector<glm::vec3> old)
// {
//     std::vector<glm::vec4> tmp(this->n_particle);
//     for (int i = 0; i < old.size(); i++)
//     {
//         tmp[i] = (glm::vec4(old[i], 0));
//     }
//     return tmp;
// }

void ParticleParticleGPU::init_SSBOs()
{
    glGenBuffers(1, &this->particle_position_SSBO);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->particle_position_SSBO);
    glBufferData(GL_SHADER_STORAGE_BUFFER, this->n_particle * 4 * sizeof(GLfloat), &this->particle_position[0], GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, this->particle_position_SSBO);

    glGenBuffers(1, &this->particle_velocity_SSBO);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->particle_velocity_SSBO);
    glBufferData(GL_SHADER_STORAGE_BUFFER, this->n_particle * 4 * sizeof(GLfloat), &this->particle_velocity[0], GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, this->particle_velocity_SSBO);

    glGenBuffers(1, &this->particle_previous_acceleration_SSBO);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->particle_previous_acceleration_SSBO);
    glBufferData(GL_SHADER_STORAGE_BUFFER, this->n_particle * 4 * sizeof(GLfloat), &this->particle_previous_acceleration[0], GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, this->particle_previous_acceleration_SSBO);

    glGenBuffers(1, &this->particle_mass_SSBO);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->particle_mass_SSBO);
    glBufferData(GL_SHADER_STORAGE_BUFFER, this->n_particle * 1 * sizeof(GLfloat), &this->particle_mass[0], GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, this->particle_mass_SSBO);

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void ParticleParticleGPU::init_compute_shader()
{
    GLuint compute_shader;
    Shader shader_program = Shader();
    switch (this->integrator)
    {
    case INTEGRATOR_EULER:
        compute_shader = shader_program.compile_shader("./shader_source/update_position_euler.comp.glsl", GL_COMPUTE_SHADER);
        break;
    case INTEGRATOR_VELOCITY_VERLET:
        compute_shader = shader_program.compile_shader("./shader_source/update_position_velocity_verlet.comp.glsl", GL_COMPUTE_SHADER);
        break;
    default:
        compute_shader = shader_program.compile_shader("./shader_source/update_position_velocity_verlet.comp.glsl", GL_COMPUTE_SHADER);
        break;
    }
    shader_program.link_shader(compute_shader);
    this->compute_shader_program = shader_program;
}

void ParticleParticleGPU::terminate()
{
    this->compute_shader_program.delete_shader();
    glDeleteBuffers(1, &this->particle_mass_SSBO);
    glDeleteBuffers(1, &this->particle_position_SSBO);
    glDeleteBuffers(1, &this->particle_previous_acceleration_SSBO);
    glDeleteBuffers(1, &this->particle_velocity_SSBO);
}