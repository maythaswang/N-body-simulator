#ifndef PARTICLE_PARTICLE_GPU_H
#define PARTICLE_PARTICLE_GPU_H
#pragma once

#include <ParticleSystem/Simulator/Simulator.h>
#include <Shader/Shader.h>

class ParticleParticleGPU : public Simulator
{
public:
    ParticleParticleGPU(GLfloat, GLfloat, GLfloat, GLfloat, SimulatorIntegrator);
    void terminate() override;

private:
    // Buffer Objects
    GLuint particle_velocity_SSBO;
    GLuint particle_previous_acceleration_SSBO;

    // Configs
    GLuint n_work_groups;
    Shader compute_shader_program;

    /**
     * @brief Update particle position
     * 
     */
    void update_position();

    /**
     * @brief Fetch SSBO data from GPU
     * 
     */
    void fetch_data();

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
     * @brief Update position of particles
     * 
     * @param old input data in form of vec3
     */
    void update_position_vector(glm::vec4 *);
};

#endif