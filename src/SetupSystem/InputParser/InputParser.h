#ifndef INPUT_PARSER_H
#define INPUT_PARSER_H
#pragma once

#include <GLcommon.h>
#include <SetupSystem/ParticleBuilder/ParticleBuilder.h>
#include <SetupSystem/DefaultTestLoader/DefaultTestLoader.h>

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
    // So that it stops screaming
    InputParser();

    /**
     * @brief Construct a new InputParser object
     *
     * @param particle_builder particle builder pointer
     */
    InputParser(ParticleBuilder *);

    /**
     * @brief Begin accepting input from user
     *
     */
    void accept_input();

    /**
     * @brief Get the summary of the setup
     *
     * @return string of setup summary
     */
    std::string get_summary();

    /**
     * @brief Get the GPU usage status
     *
     * @return 0 if not using 1 if use
     */
    bool get_use_GPU();

    /**
     * @brief Get whether the simulation will use velocity verlet or euler
     *
     * @return 0 if not using 1 if use
     */
    bool get_use_velocity_verlet();

    /**
     * @brief Get the gravitational constant
     *
     * @return gravitational constant
     */
    GLfloat get_gravitational_constant();

    /**
     * @brief Get the timestep size
     *
     * @return timestep size
     */
    GLfloat get_timestep_size();

private:
    ParticleBuilder *particle_builder;
    GLuint default_test, n_particle;
    bool use_GPU, use_default_test, use_velocity_verlet; // Well do this since there are only 2 integrators available.
    GLfloat gravitational_constant;
    GLfloat timestep_size;

    /**
     * @brief Loop (Y/N) prompt for input
     *
     * @param output output boolean
     * @param message prompt message
     */
    void input_YN(bool &output, std::string message);

    /**
     * @brief Populate simulator according to user input
     *
     */
    void populate_simulator();

    /**
     * @brief Begin manual setup from user input
     *
     */
    void manual_setup();

    /**
     * @brief Populate particles in disc shape
     *
     */
    void populate_disc();

    /**
     * @brief Populate particles in random shape
     *
     */
    void populate_random();

    /**
     * @brief Populate particles in globular cluster shape
     *
     */
    void populate_globular_cluster();

    /**
     * @brief Populate particles in sphere surface shape
     *
     */
    void populate_sphere_surface();

    /**
     * @brief Accept input for each particle cluster information.
     *
     * @param n_particle number of particles in the cluster
     * @param offset offset of particle cluster from origin
     */
    void input_basic_information(GLuint *, glm::vec3 *);

    /**
     * @brief Clear std::cin
     *
     */
    void clear_cin();

    /**
     * @brief Update particle builder setup log
     *
     */
    void update_particle_builder_setup_log();
};

#endif