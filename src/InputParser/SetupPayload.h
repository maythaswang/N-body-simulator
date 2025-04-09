#ifndef SETUP_PAYLOAD_H
#define SETUP_PAYLOAD_H
#pragma once
#include <GLCommon.h>
#include <glm/glm.hpp>

/**
 * @brief Multiple type of setup data payloads
 * 
 */

struct HeadSetupData{
    bool use_GPU, use_default, integrator; // <integrator 0: Euler, 1: Velocity verlet>
    GLuint default_test_number, num_particle;
    GLfloat gravitational_constant, timestep_size;
};

struct ParticleDiscSetupData{
    GLuint num_particles;
    glm::vec3 offset;
    GLfloat radius;
    GLfloat min_mass, max_mass;
    GLfloat min_velocity, max_velocity;
    bool is_spiral, is_dense_center;
};

struct ParticleRandomSetupData {
    GLuint num_particles;
    glm::vec3 offset;
    GLfloat radius;
    GLfloat min_mass, max_mass;
    GLfloat min_velocity, max_velocity;
};

struct ParticleGlobularClusterSetupData {
    GLuint num_particles;
    glm::vec3 offset;
    GLfloat radius;
    GLfloat min_mass, max_mass;
    GLfloat min_velocity, max_velocity;
    bool is_spiral;
};

struct ParticleSphereSurfaceSetupData {
    GLuint num_particles;
    glm::vec3 offset;
    GLfloat radius;
    GLfloat min_mass, max_mass;
    GLfloat min_velocity, max_velocity;
    bool is_spiral;
};

#endif 