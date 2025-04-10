#include "ParticleBuilder.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>

ParticleBuilder::ParticleBuilder()
{
    this->n_particle = 0;
    time_t t;
    std::srand((unsigned)time(&t));
}

void ParticleBuilder::spawn_random(ParticleRandomSetupData payload)
{
    for (int i = 0; i < payload.num_particles; i++)
    {
        glm::vec3 tmp_position = glm::vec3(random_number(-payload.radius, payload.radius), random_number(-payload.radius, payload.radius), random_number(-payload.radius, payload.radius)) + payload.offset;
        glm::vec3 tmp_velocity = glm::vec3(random_number(payload.min_velocity, payload.max_velocity), random_number(payload.min_velocity, payload.max_velocity), random_number(payload.min_velocity, payload.max_velocity));
        GLfloat tmp_mass = random_number(payload.min_mass, payload.max_mass);

        this->particle_position.push_back(glm::vec4(tmp_position, 0));
        this->particle_velocity.push_back(glm::vec4(tmp_velocity, 0));
        this->particle_acceleration.push_back(glm::vec4(0.0f));
        this->particle_mass.push_back(tmp_mass);
    }

    this->n_particle += payload.num_particles;
    this->particle_random_log.push_back(payload);
}

void ParticleBuilder::spawn_globular_cluster(ParticleGlobularClusterSetupData payload)
{
    payload.center_radius = (payload.center_radius == 0) ? 1 : payload.center_radius;

    GLfloat new_radius = std::max(payload.radius, 0.0000001f);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<float> d(0, new_radius / 2);

    for (int i = 0; i < payload.num_particles; i++)
    {

        new_radius = std::abs(d(gen));

        glm::vec3 tmp_position = glm::sphericalRand(new_radius + payload.center_radius) + payload.offset;
        glm::vec3 tmp_velocity = this->sample_velocity(tmp_position, payload.offset, payload.min_velocity, payload.max_velocity, payload.is_spiral);
        GLfloat tmp_mass = random_number(payload.min_mass, payload.max_mass);

        this->particle_position.push_back(glm::vec4(tmp_position, 0));
        this->particle_velocity.push_back(glm::vec4(tmp_velocity, 0));
        this->particle_acceleration.push_back(glm::vec4(0.0f));
        this->particle_mass.push_back(tmp_mass);
    }

    this->n_particle += payload.num_particles;
    this->particle_globular_cluster_log.push_back(payload);
}

void ParticleBuilder::spawn_sphere(ParticleSphereSurfaceSetupData payload)
{
    GLfloat new_radius = std::max(payload.radius, 0.0000001f);

    for (int i = 0; i < payload.num_particles; i++)
    {
        glm::vec3 tmp_position = glm::sphericalRand(new_radius + 1) + payload.offset;
        glm::vec3 tmp_velocity = this->sample_velocity(tmp_position, payload.offset, payload.min_velocity, payload.max_velocity, payload.is_spiral);
        GLfloat tmp_mass = random_number(payload.min_mass, payload.max_mass);

        this->particle_position.push_back(glm::vec4(tmp_position, 0));
        this->particle_velocity.push_back(glm::vec4(tmp_velocity, 0));
        this->particle_acceleration.push_back(glm::vec4(0.0f));
        this->particle_mass.push_back(tmp_mass);
    }

    this->n_particle += payload.num_particles;
    this->particle_sphere_surface_log.push_back(payload);
}

void ParticleBuilder::spawn_disc(ParticleDiscSetupData payload)
{
    GLfloat new_radius = std::max(payload.radius, 0.0000001f);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<float> d(0, new_radius / 2);

    for (int i = 0; i < payload.num_particles; i++)
    {
        if (payload.is_dense_center)
        {
            new_radius = std::abs(d(gen));
        }
        glm::vec2 disc_pos = glm::diskRand(new_radius + 1.0f);
        glm::vec3 tmp_position = glm::vec3(disc_pos.x, disc_pos.y, this->random_number(-payload.width, payload.width)) + payload.offset;
        glm::vec3 tmp_velocity = this->sample_velocity(tmp_position, payload.offset, payload.min_velocity, payload.max_velocity, payload.is_spiral);
        GLfloat tmp_mass = random_number(payload.min_mass, payload.max_mass);

        this->particle_position.push_back(glm::vec4(tmp_position, 0));
        this->particle_velocity.push_back(glm::vec4(tmp_velocity, 0));
        this->particle_acceleration.push_back(glm::vec4(0.0f));
        this->particle_mass.push_back(tmp_mass);
    }

    this->n_particle += payload.num_particles;
    this->particle_disc_log.push_back(payload);
}

void ParticleBuilder::legacy_spawn_random(GLuint n, glm::vec3 offset, GLfloat radius, GLfloat min_mass, GLfloat max_mass, GLfloat min_velocity, GLfloat max_velocity)
{
    // Add log for legacy support case
    ParticleRandomSetupData log;
    log.num_particles = n;
    log.offset = offset;
    log.radius = radius;
    log.min_mass = min_mass;
    log.max_mass = max_mass;
    log.min_velocity = min_velocity;
    log.max_velocity = max_velocity;

    this->spawn_random(log);
    // this->setup_summary.append("Random: " + std::to_string(n) + ' ' + this->format_string_vec3(offset) + ' ' + std::to_string(radius) + " (" + std::to_string(min_mass) + ", " + std::to_string(max_mass) + ") " + "(" + std::to_string(min_velocity) + ", " + std::to_string(max_velocity) + ") " + "\n");
}

void ParticleBuilder::legacy_spawn_globular_cluster(GLuint n, glm::vec3 offset, GLfloat radius, GLfloat center_radius, GLfloat min_mass, GLfloat max_mass, GLfloat min_velocity, GLfloat max_velocity, bool is_spiral, bool outer_only)
{
    ParticleGlobularClusterSetupData log;
    log.num_particles = n;
    log.offset = offset;
    log.radius = radius;
    log.center_radius = center_radius;
    log.min_mass = min_mass;
    log.max_mass = max_mass;
    log.min_velocity = min_velocity;
    log.max_velocity = max_velocity;
    log.is_spiral = is_spiral;

    this->spawn_globular_cluster(log);
}

void ParticleBuilder::legacy_spawn_sphere(GLuint n, glm::vec3 offset, GLfloat radius, GLfloat min_mass, GLfloat max_mass, GLfloat min_velocity, GLfloat max_velocity, bool is_spiral)
{
    ParticleSphereSurfaceSetupData log;
    log.num_particles = n;
    log.offset = offset;
    log.radius = radius;
    log.min_mass = min_mass;
    log.max_mass = max_mass;
    log.min_velocity = min_velocity;
    log.max_velocity = max_velocity;
    log.is_spiral = is_spiral;

    this->spawn_sphere(log);
}

void ParticleBuilder::legacy_spawn_double_sphere(GLuint n, glm::vec3 offset, GLfloat radius, GLfloat center_radius, GLfloat min_mass, GLfloat max_mass, GLfloat min_velocity, GLfloat max_velocity, bool is_spiral)
{   
    ParticleSphereSurfaceSetupData payload_1, payload_2;
    // Payload 1 setup
    payload_1.num_particles = (int)std::ceil(n / 2);
    payload_1.offset = offset;
    payload_1.radius = radius;
    payload_1.min_mass = min_mass;
    payload_1.max_mass = max_mass;
    payload_1.min_velocity = min_velocity;
    payload_1.max_velocity = max_velocity;
    payload_1.is_spiral = is_spiral;

    // Payload 2 setup
    payload_2.num_particles = (int)std::floor(n / 2);
    payload_2.offset = offset;
    payload_2.radius = center_radius;
    payload_2.min_mass = min_mass;
    payload_2.max_mass = max_mass;
    payload_2.min_velocity = min_velocity;
    payload_2.max_velocity = max_velocity;
    payload_2.is_spiral = is_spiral;

    this->spawn_sphere(payload_1);
    this->spawn_sphere(payload_2);
}

void ParticleBuilder::legacy_spawn_disc(GLuint n, glm::vec3 offset, GLfloat radius, GLfloat width, GLfloat min_mass, GLfloat max_mass, GLfloat min_velocity, GLfloat max_velocity, bool is_spiral, bool dense_center)
{
    ParticleDiscSetupData log;
    log.num_particles = n;
    log.offset = offset;
    log.radius = radius;
    log.width = width;
    log.min_mass = min_mass;
    log.max_mass = max_mass;
    log.min_velocity = min_velocity;
    log.max_velocity = max_velocity;
    log.is_spiral = is_spiral;
    log.is_dense_center = dense_center;
    this->spawn_disc(log);
}

bool ParticleBuilder::populate_vectors(GLuint *n, std::vector<glm::vec4> *particle_position, std::vector<glm::vec4> *particle_velocity, std::vector<glm::vec4> *particle_acceleration, std::vector<GLfloat> *particle_mass)
{
    if (!this->n_particle || !n || !particle_position || !particle_velocity || !particle_acceleration || !particle_mass)
    {
        return 0;
    }

    *n = this->n_particle;
    *particle_position = this->particle_position;
    *particle_velocity = this->particle_velocity;
    *particle_acceleration = this->particle_acceleration;
    *particle_mass = this->particle_mass;
    this->head_setup_data.num_particle = this->n_particle;
    return 1;
}

void ParticleBuilder::reset_vectors()
{
    this->n_particle = 0;
    this->particle_position.clear();
    this->particle_velocity.clear();
    this->particle_mass.clear();
    this->particle_acceleration.clear();
}

GLfloat ParticleBuilder::random_number(GLfloat min_value, GLfloat max_value)
{
    return min_value + (((GLfloat)rand()) / ((GLfloat)(RAND_MAX))) * (max_value - min_value);
}

glm::vec3 ParticleBuilder::sample_velocity(glm::vec3 position, glm::vec3 offset, GLfloat min_velocity, GLfloat max_velocity, bool is_spiral)
{
    if (is_spiral)
    {
        glm::vec3 distance = position - offset;
        if (distance == glm::vec3(0.0f))
        {
            return glm::vec3(0.0f);
        }

        glm::vec3 direction = glm::normalize(distance);
        glm::vec3 up = glm::vec3(0.0f, 0.0f, 1.0f);
        glm::vec3 right = glm::cross(direction, up);
        return right * random_number(min_velocity, max_velocity);
    }

    return glm::vec3(random_number(min_velocity, max_velocity), random_number(min_velocity, max_velocity), random_number(min_velocity, max_velocity));
}