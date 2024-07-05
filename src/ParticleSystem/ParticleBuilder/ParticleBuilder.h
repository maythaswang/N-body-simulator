#pragma once
#include <GLCommon.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/random.hpp>
#include <math.h>
#include <vector>
class ParticleBuilder
{
public:
    ParticleBuilder();
    void spawn_random(GLuint n, glm::vec3 offset, GLfloat radius, GLfloat min_mass, GLfloat max_mass, GLfloat min_velocity, GLfloat max_velocity);
    void spawn_globular_cluster(GLuint n, glm::vec3 offset, GLfloat radius, GLfloat center_radius, GLfloat min_mass, GLfloat max_mass, GLfloat min_velocity, GLfloat max_velocity, bool is_spiral, bool is_dense, bool outer_only);
    void spawn_sphere(GLuint n, glm::vec3 offset, GLfloat radius, GLfloat min_mass, GLfloat max_mass, GLfloat min_velocity, GLfloat max_velocity, bool is_spiral);
    bool populate_vectors(GLuint *, std::vector<glm::vec3> *, std::vector<glm::vec3> *, std::vector<glm::vec3> *, std::vector<GLfloat> *);

private:
    std::vector<glm::vec3> particle_position;
    std::vector<glm::vec3> particle_velocity;
    std::vector<glm::vec3> particle_acceleration;
    std::vector<GLfloat> particle_mass;
    GLuint n_particle;

    GLfloat random_number(GLfloat, GLfloat);
    void reset_vectors();
};