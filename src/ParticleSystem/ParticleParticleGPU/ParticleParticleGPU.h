#pragma once
#include <Simulator.h>
#include <Shader.h>
class ParticleParticleGPU : public Simulator
{
public:
    ParticleParticleGPU(GLfloat, GLfloat, GLfloat, GLfloat, SimulatorIntegrator);
    void terminate();

private:
    GLuint particle_position_SSBO;
    GLuint particle_velocity_SSBO;
    GLuint particle_acceleration_SSBO;
    GLuint particle_previous_acceleration_SSBO;
    GLuint particle_mass_SSBO;
    GLuint n_work_groups;
    Shader compute_shader_program;
    
    std::vector<glm::vec4> particle_pos_vec4;
    std::vector<glm::vec4> particle_vel_vec4;
    std::vector<glm::vec4> particle_acc_vec4;

    void update_position();

    void load_particles(GLuint, std::vector<glm::vec3>, std::vector<glm::vec3>, std::vector<glm::vec3>, std::vector<GLfloat>) override;

    void next_step() override;
    
    void fetch_particle_data();
    void init_SSBOs();
    void init_compute_shader();

    std::vector<glm::vec4> convert_to_vec4(std::vector<glm::vec3> );

    void update_position_vector(glm::vec4 *);
};