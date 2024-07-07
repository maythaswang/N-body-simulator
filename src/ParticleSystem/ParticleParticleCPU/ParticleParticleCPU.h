#pragma once
#include <Simulator.h>
class ParticleParticleCPU : public Simulator
{
public:
    ParticleParticleCPU(GLfloat, GLfloat, GLfloat, GLfloat);

private:
    glm::vec3 calculate_acceleration(uint32_t, uint32_t) override;

    void update_position_euler() override;

    void update_position_velocity_verlet() override;
};