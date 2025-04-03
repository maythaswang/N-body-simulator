#pragma once
#include <Simulator.h>
class ParticleParticleCPU : public Simulator
{
public:
    ParticleParticleCPU(GLfloat, GLfloat, GLfloat, GLfloat, SimulatorIntegrator);

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
    glm::vec3 calculate_acceleration(uint32_t, uint32_t);

    void update_position_euler() override;

    void update_position_velocity_verlet() override;



    void load_particles(GLuint, std::vector<glm::vec4>, std::vector<glm::vec4>, std::vector<glm::vec4>, std::vector<GLfloat>) override;
};