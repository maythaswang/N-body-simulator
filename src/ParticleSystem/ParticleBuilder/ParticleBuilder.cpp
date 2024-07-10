#include <ParticleBuilder.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>

ParticleBuilder::ParticleBuilder()
{
    this->n_particle = 0;
    time_t t;
    std::srand((unsigned)time(&t));
}

void ParticleBuilder::spawn_random(GLuint n, glm::vec3 offset, GLfloat radius, GLfloat min_mass, GLfloat max_mass, GLfloat min_velocity, GLfloat max_velocity)
{
    for (int i = 0; i < n; i++)
    {
        glm::vec3 tmp_position = glm::vec3(random_number(-radius, radius), random_number(-radius, radius), random_number(-radius, radius)) + offset;
        glm::vec3 tmp_velocity = glm::vec3(random_number(min_velocity, max_velocity), random_number(min_velocity, max_velocity), random_number(min_velocity, max_velocity));
        GLfloat tmp_mass = random_number(min_mass, max_mass);

        this->particle_position.push_back(tmp_position);
        this->particle_velocity.push_back(tmp_velocity);
        this->particle_acceleration.push_back(glm::vec3(0.0f));
        this->particle_mass.push_back(tmp_mass);
    }

    this->n_particle += n;
}

void ParticleBuilder::spawn_globular_cluster(GLuint n, glm::vec3 offset, GLfloat radius, GLfloat center_radius, GLfloat min_mass, GLfloat max_mass, GLfloat min_velocity, GLfloat max_velocity, bool is_spiral, bool is_dense, bool outer_only)
{
    center_radius = (center_radius == 0) ? 1 : center_radius;

    GLfloat radius_multiplier;
    for (int i = 0; i < n; i++)
    {
        radius_multiplier = (outer_only) ? 1 : (is_dense) ? glm::linearRand(0, 1)
                                                          : random_number(0.0f, 1.0f);
        glm::vec3 tmp_position = glm::sphericalRand(radius * radius_multiplier + center_radius) + offset;
        glm::vec3 tmp_velocity = this->sample_velocity(tmp_position, offset, min_velocity, max_velocity, is_spiral);
        GLfloat tmp_mass = random_number(min_mass, max_mass);

        this->particle_position.push_back(tmp_position);
        this->particle_velocity.push_back(tmp_velocity);
        this->particle_acceleration.push_back(glm::vec3(0.0f));
        this->particle_mass.push_back(tmp_mass);
    }

    this->n_particle += n;
}

void ParticleBuilder::spawn_sphere(GLuint n, glm::vec3 offset, GLfloat radius, GLfloat min_mass, GLfloat max_mass, GLfloat min_velocity, GLfloat max_velocity, bool is_spiral)
{
    this->spawn_globular_cluster(n, offset, radius, 0, min_mass, max_mass, min_velocity, max_velocity, is_spiral, 0, 1);
}

bool ParticleBuilder::populate_vectors(GLuint *n, std::vector<glm::vec3> *particle_position, std::vector<glm::vec3> *particle_velocity, std::vector<glm::vec3> *particle_acceleration, std::vector<GLfloat> *particle_mass)
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

void ParticleBuilder::spawn_disc(GLuint n, glm::vec3 offset, GLfloat radius, GLfloat width, GLfloat min_mass, GLfloat max_mass, GLfloat min_velocity, GLfloat max_velocity, bool is_spiral)
{

    for (int i = 0; i < n; i++)
    {
        glm::vec2 disc_pos = glm::diskRand(radius);
        glm::vec3 tmp_position = glm::vec3(disc_pos.x, disc_pos.y, this->random_number(-width, width)) + offset;
        glm::vec3 tmp_velocity = this->sample_velocity(tmp_position, offset, min_velocity, max_velocity, is_spiral);
        GLfloat tmp_mass = random_number(min_mass, max_mass);

        this->particle_position.push_back(tmp_position);
        this->particle_velocity.push_back(tmp_velocity);
        this->particle_acceleration.push_back(glm::vec3(0.0f));
        this->particle_mass.push_back(tmp_mass);
    }

    this->n_particle += n;
}