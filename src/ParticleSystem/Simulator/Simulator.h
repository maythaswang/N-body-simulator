#pragma once
#include <GLCommon.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/random.hpp>
#include <SimulatorEnum.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <string>

/**
 * @brief This simulator is implemented using Sequential Particle-Particle method O(n^2) on CPU
 *
 */
class Simulator
{
public:
    /**
     * @brief Calculate the next step of the simulation
     *
     */
    virtual void next_step();

    /**
     * @brief Initialize VAO and VBO with the particle informations
     * @warning DEPRECATE SOON IN FAVOR OF MOVING TO USING PURE SSBO
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
    virtual void load_particles(GLuint, std::vector<glm::vec4>, std::vector<glm::vec4>, std::vector<glm::vec4>, std::vector<GLfloat>);

    /**
     * @brief Get the running state object
     * 
     * @return true 
     * @return false 
     */
    bool get_running_state();

    /**
     * @brief Set the running state
     * 
     */
    void set_running_state(bool);

    /**
     * @brief Get the current step of the simulation
     * 
     * @return GLuint 
     */
    GLuint get_current_step();

    /**
     * @brief Get the timestep size of the simulation
     * 
     * @return GLfloat 
     */
    GLfloat get_timestep_size();

    /**
     * @brief Get the number of particles in the simulation
     * 
     * @return GLuint 
     */
    GLuint get_n_particle();
    
    /**
     * @brief Delete and free all components needed to be freed.
     * 
     */
    virtual void terminate();

    /**
     * @brief Get simulator setup log.
     * 
     * @return string of the details of simulator setup.
     */
    std::string get_setup_log();

    /**
     * @brief Append information to the setup log.
     * @param input Information string
     * 
     */
    void append_setup_log(std::string);

// I'll just declare it all protected since it's only me working on this.
protected:
    // Particle data
    std::vector<glm::vec4> particle_position;
    std::vector<glm::vec4> particle_velocity;
    std::vector<glm::vec4> particle_previous_acceleration;
    std::vector<GLfloat> particle_mass;

    // Simulation variables
    GLfloat gravitational_constant;
    GLfloat softening_factor;
    GLfloat timestep_size;
    GLuint n_particle;

    // log
    GLuint current_step;

    // Bufs (TODO: Deprecate)
    GLuint *VAO;
    GLuint *VBO;
    
    // SSBO for postion and mass (This will govern the postion of each instance and its color:mass)
    GLuint particle_position_SSBO; 
    GLuint particle_mass_SSBO; 
    
    SimulatorIntegrator integrator;
    
    std::string setup_log;

    bool running_state;

    /**
     * @brief Construct a new Simulator:: Simulator object
     *
     * @param n_particle number of particles
     * @param gravitational_constant gravitational constant
     * @param softening_factor softening factor 
     * @param timestep_size timestep size (per frame)
     * @param integrator integrator
     */
    Simulator(GLfloat, GLfloat, GLfloat, GLfloat, SimulatorIntegrator);



    /**
     * @brief Update the position of each particle using semi-implicit euler method as the integrator
     * @note v = dx/dt, a = dv/dt
     * @note dx = v * dt, dv = a * dt
     * @note x_n+1 = x_n + h * dx, v_n+1 = v_n + h * dv
     */
    virtual void update_position_euler() ;

    /**
     * @brief Update the position of each particle using Velocity-Verlet method as the integrator
     * @note Aka. KDK (Kick-Drift-Kick) Leapfrog
     * @note v(t + 1/2δt) = v(t) + 1/2 * a(t) * δt
     * @note x(t + δt) = x(t) + v(t+ 1/2δt) * δt
     * @note a(t + δt) = Calculate acceleration as usual using the new position x(t+δt)
     * @note v(t + δt) = v(t + 1/2δt) + 1/2 * a(t + δt) * δt
     */
    virtual void update_position_velocity_verlet();
};