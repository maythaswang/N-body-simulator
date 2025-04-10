#ifndef PARTICLE_PARTICLE_CPU_H
#define PARTICLE_PARTICLE_CPU_H
#pragma once

#include <ParticleSystem/Simulator/Simulator.h>

class ParticleParticleCPU : public Simulator
{
public:
    ParticleParticleCPU(GLfloat, GLfloat, GLfloat, GLfloat, SimulatorIntegrator, SimulatorImplementation);

private:
    std::vector<glm::vec4> particle_acceleration;

    /**
     * @brief Calculate acceleration between the two particles
     *
     * @note F = Gmm/r^2 * -r/||r||, F = ma
     * @note ma = Gmm/r^2 * -r/||r||
     * @note a = G ∑ m/r^2 * -r/||r||
     * @param current
     * @param other
     * @return acceleration of the particle "current" based on force being exerted from the particle "other"
     */
    glm::vec4 calculate_acceleration(uint32_t, uint32_t);

    void update_position_euler() override;

    void update_position_velocity_verlet() override;

    void init_SSBOs();

    void load_particles(GLuint, std::vector<glm::vec4>, std::vector<glm::vec4>, std::vector<glm::vec4>, std::vector<GLfloat>) override;

    void update_SSBO();
};

#endif