#pragma once
#include <GLcommon.h>
#include <ParticleBuilder.h>
#include <DefaultTestLoader.h>

#include <iostream>
#include <string>
#include <sstream>

/**
 * @brief Parse input from user for setting up the particle simulator.
 * @warning This class is a complete mess. This is just a makeshift solution.
 */
class InputParser
{
public:
    InputParser(ParticleBuilder *);

    void accept_input();
    std::string get_summary();

    bool get_use_GPU();
    bool get_use_velocity_verlet();
    GLfloat get_gravitational_constant();
    GLfloat get_timestep_size();

private:
    ParticleBuilder *particle_builder;
    GLuint default_test, n_particle;
    bool use_GPU, use_default_test, use_velocity_verlet; // Well do this since there are only 2 integrators available.
    GLfloat gravitational_constant;
    GLfloat timestep_size;

    void input_YN(bool &output, std::string message);
    void populate_simulator();
    void manual_setup();

    void populate_disc();
    void populate_random();
    void populate_globular_cluster();
    void populate_sphere_surface();

    void input_basic_information(GLuint *, glm::vec3 *);
    void clear_cin();
};