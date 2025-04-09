#ifndef PARTICLE_BUILDER_H
#define PARTICLE_BUILDER_H
#pragma once

#include <GLCommon.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/random.hpp>
#include <SetupSystem/SetupPayload.h>
#include <math.h>
#include <vector>
#include <string>
#include <random>

/**
 * @brief Build vectors of particle data in preparation for Simulation.
 * @note Honestly? This is a big mess, I don't know that was on my mind when I first built this but then now it's too late to fix anything (not really too late but maybe later???) 
 * and I really am getting tired of all this, to anyone who were reading this, I'm sorry lol.....
 * @warning This implementation is not threadsafe.
 */


class ParticleBuilder
{
public:
    /**
     * @brief Construct a new Particle Builder object
     *
     */
    ParticleBuilder();

    /**
     * @brief Spawn particles at random (might look cubic) and stores it into the intermediate vector.
     *
     * @param n number of particles
     * @param offset offset of the center of the region from the origin
     * @param radius radius of the region
     * @param min_mass minimum particle mass
     * @param max_mass maximum particle mass
     * @param min_velocity maximum particle velocity
     * @param max_velocity minimum particle velocity
     */
    void legacy_spawn_random(GLuint, glm::vec3, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);

    /**
     * @brief Spawn particles into the form of globular cluster and stores it into the intermediate vector.
     *
     * @param n number of particles
     * @param offset offset of the center of the sphere from the origin.
     * @param radius radius of the sphere.
     * @param center_radius radius of the most dense part
     * @param min_mass minimum particle mass
     * @param max_mass maximum particle mass
     * @param min_velocity minimum particle velocity
     * @param max_velocity maximum particle velocity
     * @param is_spiral set the velocity of the particles such that they all move in a spiral
     * @param outer_only spawn particles only on the surface of the sphere.
     */
    void legacy_spawn_globular_cluster(GLuint, glm::vec3, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, bool, bool);

    /**
     * @brief Spawn particles on the surface of the sphere and store it into the intermediate vector.
     *
     * @param n number of particles
     * @param offset offset of the center of the sphere from the origin.
     * @param radius radius of the sphere.
     * @param min_mass minimum particle mass
     * @param max_mass maximum particle mass
     * @param min_velocity minimum particle velocity
     * @param max_velocity maximum particle velocity
     * @param is_spiral set the velocity of the particles such that they all move in a spiral
     */
    void legacy_spawn_sphere(GLuint, glm::vec3, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, bool);

    /**
     * @brief Spawn particles on a form of disc and store it into the intermediate vector.
     *
     * @param n number of particles
     * @param offset offset of the center of the disc from origin
     * @param radius radius of the disc
     * @param width width of the disc
     * @param min_mass minimum particle mass
     * @param max_mass maximum particle mass
     * @param min_velocity minimum particle velocity
     * @param max_velocity maximum particle velocity
     * @param is_spiral set the velocity of the particles such that they all move in a spiral.
     * @param dense_center place particles using normal distribution about the center point of the disc
     */
    void legacy_spawn_disc(GLuint, glm::vec3, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, bool, bool);

    /**
     * @brief Spawn particles on the surface of the sphere and store it into the intermediate vector.
     * @note This function exist only to support some legacy test cases.
     *
     * @param n number of particles
     * @param offset offset of the center of the sphere from the origin.
     * @param radius radius of the sphere.
     * @param center_radius radius of the inner sphere
     * @param min_mass minimum particle mass
     * @param max_mass maximum particle mass
     * @param min_velocity minimum particle velocity
     * @param max_velocity maximum particle velocity
     * @param is_spiral set the velocity of the particles such that they all move in a spiral
     */
    void legacy_spawn_double_sphere(GLuint n, glm::vec3 offset, GLfloat radius, GLfloat center_radius, GLfloat min_mass, GLfloat max_mass, GLfloat min_velocity, GLfloat max_velocity, bool is_spiral);

    void spawn_random(ParticleRandomSetupData particle_random_setup_data);
    void spawn_globular_cluster(ParticleGlobularClusterSetupData particle_globular_cluster_setup_data);
    void spawn_sphere(ParticleSphereSurfaceSetupData particle_sphere_setup_data);
    void spawn_disc(ParticleDiscSetupData particle_disc_setup_data);


    /**
     * @brief populate vectors user inputted through the parameters using the stored particle data. Afterwards the stored particle data is resetted.
     *
     * @param n number of particles
     * @param particle_position vector of particle's position
     * @param particle_velocity vector of particle's velocity
     * @param particle_acceleration vector of particle's acceleration
     * @param particle_mass vector of particle's mass
     * @return completion status
     */
    bool populate_vectors(GLuint *, std::vector<glm::vec4> *, std::vector<glm::vec4> *, std::vector<glm::vec4> *, std::vector<GLfloat> *);

    /**
     * @brief provide summary string of the simulation setup
     *
     * @return simulation setup information
     */
    std::string get_summary();

    // Setup Summary (publicly accessible for GUI to handle more stuffs)
    // In summary, I am getting lazy...
    HeadSetupData head_setup_data;
    std::vector<ParticleDiscSetupData> particle_disc_log;
    std::vector<ParticleRandomSetupData> particle_random_log;
    std::vector<ParticleGlobularClusterSetupData> particle_globular_cluster_log;
    std::vector<ParticleSphereSurfaceSetupData> particle_sphere_surface_log;

private:
    std::vector<glm::vec4> particle_position;
    std::vector<glm::vec4> particle_velocity;
    std::vector<glm::vec4> particle_acceleration;
    std::vector<GLfloat> particle_mass;
    GLuint n_particle;

    // Setup Summary
    std::string setup_summary;

    /**
     * @brief Number Randomizer
     * @param min_value minimum value for randomizing
     * @param max_value maximum value for randomizing
     *
     * @return GLfloat
     */
    GLfloat random_number(GLfloat, GLfloat);

    /**
     * @brief Reset all vector data to 0
     *
     */
    void reset_vectors();

    /**
     * @brief Assign velocity to each particle based on settings
     *
     * @param position vector of particle's position
     * @param offset offset of the center of the particle cluster from origin
     * @param min_velocity minimum particle velocity
     * @param max_velocity maximum particle velocity
     * @param is_spiral set the velocity of the particles such that they all move in a spiral
     * @return vector of particle's velocity
     */
    glm::vec3 sample_velocity(glm::vec3, glm::vec3, GLfloat, GLfloat, bool);

    /**
     * @brief format vec3 into string (x, y ,z)
     *
     * @return vec3 information in terms of string
     */
    std::string format_string_vec3(glm::vec3);

    /**
     * @brief Spawn particles into the form of globular cluster and stores it into the intermediate vector.
     *
     * @param n number of particles
     * @param offset offset of the center of the sphere from the origin.
     * @param radius radius of the sphere.
     * @param center_radius radius of the most dense part
     * @param min_mass minimum particle mass
     * @param max_mass maximum particle mass
     * @param min_velocity minimum particle velocity
     * @param max_velocity maximum particle velocity
     * @param is_spiral set the velocity of the particles such that they all move in a spiral
     * @param outer_only spawn particles only on the surface of the sphere.
     */
    void spherical_cluster_helper(GLuint, glm::vec3, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, bool, bool);
};

#endif