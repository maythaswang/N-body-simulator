#pragma once
#include <GLCommon.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/random.hpp>
#include <math.h>
#include <vector>
#include <string>

/**
 * @brief Build vectors of particle data in preparation for Simulation.
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
    void spawn_random(GLuint, glm::vec3, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);

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
     * @param is_dense increase the number of particles in the region of center_radius by a substantial amount
     * @param outer_only spawn particles only on the surface of the sphere.
     */
    void spawn_globular_cluster(GLuint, glm::vec3, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, bool, bool, bool);

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
    void spawn_sphere(GLuint, glm::vec3, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, bool);

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
     */
    void spawn_disc(GLuint , glm::vec3 , GLfloat , GLfloat , GLfloat , GLfloat , GLfloat , GLfloat , bool );

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
    bool populate_vectors(GLuint *, std::vector<glm::vec3> *, std::vector<glm::vec3> *, std::vector<glm::vec3> *, std::vector<GLfloat> *);

    std::string get_summary();
private:
    std::vector<glm::vec3> particle_position;
    std::vector<glm::vec3> particle_velocity;
    std::vector<glm::vec3> particle_acceleration;
    std::vector<GLfloat> particle_mass;
    GLuint n_particle;
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

    glm::vec3 sample_velocity(glm::vec3, glm::vec3, GLfloat, GLfloat, bool);

    std::string format_string_vec3(glm::vec3);

};