#pragma once
#include <GLCommon.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/random.hpp>
#include <math.h>
#include <vector>

/**
 * @brief This simulator is implemented using Sequential Particle-Particle method O(n^2) on CPU
 *
 */
class Simulator
{
public:
    /**
     * @brief Construct a new Simulator:: Simulator object
     *
     * @param n_particle number of particles
     * @param gravitational_constant gravitational constant
     * @param softening_factor softening factor 
     * @param timestep_size timestep size (per frame)
     */
    Simulator(GLfloat, GLfloat, GLfloat, GLfloat);

    /**
     * @brief Calculate the next step of the simulation
     *
     */
    void next_step();

    /**
     * @brief Initialize VAO and VBO with the particle informations
     * @param VAO Vertex Array Object pointer 
     * @param VBO Vertex Buffer Object pointer
     */
    void initialize_particles(GLuint *, GLuint *);

    /**
     * @brief Load particles information from the input vector into the simulation.
     * @param n_particles number of particles
     * @param position vector of particle position
     * @param velocity vector of particle velocity 
     * @param previous_acceleration vector of particle acceleration in the previous step.
     * @param mass vector of particle mass
     */
    void load_particles(GLuint, std::vector<glm::vec3>, std::vector<glm::vec3>, std::vector<glm::vec3>, std::vector<GLfloat>);

    bool get_running_state();
    void set_running_state(bool);

    GLuint get_current_step();
    GLfloat get_timestep_size();
    GLuint get_n_particle();

private:
    std::vector<glm::vec3> particle_position;
    std::vector<glm::vec3> particle_velocity;
    std::vector<glm::vec3> particle_acceleration;
    std::vector<glm::vec3> particle_previous_acceleration;
    std::vector<GLfloat> particle_mass;
    GLfloat gravitational_constant;
    GLfloat softening_factor;
    GLfloat timestep_size;
    GLfloat n_particle;
    GLuint current_step;
    GLuint *VAO;
    GLuint *VBO;
    bool running_state;

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

    /**
     * @brief Update the position of each particle using semi-implicit euler method as the integrator
     * @note v = dx/dt, a = dv/dt
     * @note dx = v * dt, dv = a * dt
     * @note x_n+1 = x_n + h * dx, v_n+1 = v_n + h * dv
     */
    void update_position_euler();

    /**
     * @brief Update the position of each particle using Velocity-Verlet method as the integrator
     * @note Aka. KDK (Kick-Drift-Kick) Leapfrog
     * @note v(t + 1/2δt) = v(t) + 1/2 * a(t) * δt
     * @note x(t + δt) = x(t) + v(t+ 1/2δt) * δt
     * @note a(t + δt) = Calculate acceleration as usual using the new position x(t+δt)
     * @note v(t + δt) = v(t + 1/2δt) + 1/2 * a(t + δt) * δt
     */
    void update_position_velocity_verlet();
};