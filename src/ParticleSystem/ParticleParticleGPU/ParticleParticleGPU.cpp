#include <ParticleParticleGPU.h>

ParticleParticleGPU::ParticleParticleGPU(GLfloat n_particle, GLfloat gravitational_constant, GLfloat softening_factor, GLfloat timestep_size) : Simulator(n_particle, gravitational_constant, softening_factor, timestep_size)
{
}

void ParticleParticleGPU::next_step()
{

    // this->update_position_euler();
    this->update_position_velocity_verlet();


    glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->particle_position_SSBO);
    glm::vec4 *rtn = static_cast<glm::vec4 *>(glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_ONLY));
    glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
    // std::copy(rtn[0], rtn[this->n_particle], std::back_inserter(this->particle_position));
    // this->update_position_euler();
    //
    this->particle_position = this->convert_to_vec3(rtn);
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * this->n_particle * 3, &this->particle_position[0]);
    // for (int i = 0; i < 1; i++)
    // {
    //     std::cout << "shader: " << rtn[i][0] << ' ' << rtn[i][1] << ' ' << rtn[i][2] << std::endl;
    //     std::cout << "real pos: " << this->particle_pos_vec4[i][0] << ' ' << this->particle_pos_vec4[i][1] << ' ' << this->particle_pos_vec4[i][2] << std::endl;
    //     std::cout << "real vel: " << this->particle_vel_vec4[i][0] << ' ' << this->particle_vel_vec4[i][1] << ' ' << this->particle_vel_vec4[i][2] << std::endl;
    //     std::cout << "real acc: " << this->particle_acc_vec4[i][0] << ' ' << this->particle_acc_vec4[i][1] << ' ' << this->particle_acc_vec4[i][2] << std::endl;
    // }
    // std::cout << std::endl;

    this->current_step += 1;
}

// TODO: Do something that is not as ugly as this.
std::vector<glm::vec3> ParticleParticleGPU::convert_to_vec3(glm::vec4 * old){
    std::vector<glm::vec3> tmp(this->n_particle);
    for(int i = 0; i < this->n_particle; i++){
        tmp[i] = (glm::vec3(old[i].x, old[i].y, old[i].z));
    }
    return tmp;
}

void ParticleParticleGPU::update_position_euler()
{
    this->compute_shader_program.use();
    this->compute_shader_program.set_float("gravitational_constant", this->gravitational_constant);
    this->compute_shader_program.set_float("softening_factor", this->softening_factor);
    this->compute_shader_program.set_float("timestep_size", this->timestep_size);
    this->compute_shader_program.set_int("n_particle", this->n_particle);
    glDispatchCompute(157, 1, 1); //TODO: CHANGE THIS
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
}

void ParticleParticleGPU::update_position_velocity_verlet()
{
    this->compute_shader_program.use();
    this->compute_shader_program.set_float("gravitational_constant", this->gravitational_constant);
    this->compute_shader_program.set_float("softening_factor", this->softening_factor);
    this->compute_shader_program.set_float("timestep_size", this->timestep_size);
    this->compute_shader_program.set_int("n_particle", this->n_particle);
    glDispatchCompute(157, 1, 1); //TODO: CHANGE THIS
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
}

void ParticleParticleGPU::load_particles(GLuint n, std::vector<glm::vec3> position, std::vector<glm::vec3> velocity, std::vector<glm::vec3> previous_acceleration, std::vector<GLfloat> mass)
{
    this->n_particle = n;
    this->particle_position = position; 
    this->particle_pos_vec4 = this->convert_to_vec4(position);
    this->particle_vel_vec4 = this->convert_to_vec4(velocity);
    this->particle_acc_vec4 = this->convert_to_vec4(previous_acceleration);
    this->particle_mass = mass;

    this->init_compute_shader();
    this->init_SSBOs();
}

std::vector<glm::vec4> ParticleParticleGPU::convert_to_vec4(std::vector<glm::vec3> old){
    std::vector<glm::vec4> tmp(this->n_particle);
    for(int i = 0; i < old.size(); i++){
        tmp[i] = (glm::vec4(old[i],0));
    }
    return tmp;
}

void ParticleParticleGPU::init_SSBOs()
{
    glGenBuffers(1, &this->particle_position_SSBO);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->particle_position_SSBO);
    glBufferData(GL_SHADER_STORAGE_BUFFER, this->n_particle * 4 * sizeof(GLfloat), &this->particle_pos_vec4[0], GL_DYNAMIC_COPY);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, this->particle_position_SSBO);

    glGenBuffers(1, &this->particle_velocity_SSBO);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->particle_velocity_SSBO);
    glBufferData(GL_SHADER_STORAGE_BUFFER, this->n_particle * 4 * sizeof(GLfloat), &this->particle_vel_vec4[0], GL_DYNAMIC_COPY);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, this->particle_velocity_SSBO);

    glGenBuffers(1, &this->particle_previous_acceleration_SSBO);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->particle_previous_acceleration_SSBO);
    glBufferData(GL_SHADER_STORAGE_BUFFER, this->n_particle * 4 * sizeof(GLfloat), &this->particle_acc_vec4[0], GL_DYNAMIC_COPY);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, this->particle_previous_acceleration_SSBO);

    glGenBuffers(1, &this->particle_mass_SSBO);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->particle_mass_SSBO);
    glBufferData(GL_SHADER_STORAGE_BUFFER, this->n_particle * 1 * sizeof(GLfloat), &this->particle_mass[0], GL_DYNAMIC_COPY);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, this->particle_mass_SSBO);

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void ParticleParticleGPU::init_compute_shader()
{
    Shader shader_program = Shader();
    // GLuint compute_shader = shader_program.compile_shader("./shader_source/update_position_euler.comp.glsl", GL_COMPUTE_SHADER);
    GLuint compute_shader = shader_program.compile_shader("./shader_source/update_position_velocity_verlet.comp.glsl", GL_COMPUTE_SHADER);
    shader_program.link_shader(compute_shader);
    this->compute_shader_program = shader_program;
}

void ParticleParticleGPU::terminate()
{
    this->compute_shader_program.delete_shader();
}