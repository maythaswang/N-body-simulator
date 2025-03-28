#pragma once
#include <Simulator.h>
#include <Shader.h>
class ParticleParticleGPU : public Simulator
{
public:
    ParticleParticleGPU(GLfloat, GLfloat, GLfloat, GLfloat, SimulatorIntegrator);
    void terminate() override;

private:
    // Buffer Objects
    GLuint particle_position_SSBO;
    GLuint particle_velocity_SSBO;
    GLuint particle_acceleration_SSBO;
    GLuint particle_previous_acceleration_SSBO;
    GLuint particle_mass_SSBO;

    // Configs
    GLuint n_work_groups;
    Shader compute_shader_program;
    
    // Deprecate this soon
    // std::vector<glm::vec4> particle_pos_vec4;
    // std::vector<glm::vec4> particle_vel_vec4;
    // std::vector<glm::vec4> particle_acc_vec4;

    /**
     * @brief Update particle position
     * 
     */
    void update_position();

    void load_particles(GLuint, std::vector<glm::vec4>, std::vector<glm::vec4>, std::vector<glm::vec4>, std::vector<GLfloat>) override;

    void next_step() override;
    
    /**
     * @brief Initialize SSBO for storing data
     * 
     */
    void init_SSBOs();

    /**
     * @brief Initalize compute shader
     * 
     */
    void init_compute_shader();

    /**
     * @brief Convert vector of vec3 to vec4
     * @note DEPRECATED
     * 
     * @param old input data in form of vec3
     * @return vector of vec4
     */
    // std::vector<glm::vec4> convert_to_vec4(std::vector<glm::vec3> );

    /**
     * @brief Update position of particles
     * 
     * @param old input data in form of vec3
     */
    void update_position_vector(glm::vec4 *);
};