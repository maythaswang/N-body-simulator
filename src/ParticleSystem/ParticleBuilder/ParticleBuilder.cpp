#include <ParticleBuilder.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>

ParticleBuilder::ParticleBuilder()
{
    this->n_particle = 0;
    this->setup_summary = "";
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
    this->setup_summary.append("Random: " + std::to_string(n) + ' ' + this->format_string_vec3(offset) + ' ' + std::to_string(radius) + " (" + std::to_string(min_mass) + ", " + std::to_string(max_mass) + ") " + "(" + std::to_string(min_velocity) + ", " + std::to_string(max_velocity) + ") " + "\n");
}

void ParticleBuilder::spawn_globular_cluster(GLuint n, glm::vec3 offset, GLfloat radius, GLfloat center_radius, GLfloat min_mass, GLfloat max_mass, GLfloat min_velocity, GLfloat max_velocity, bool is_spiral, bool outer_only)
{
    center_radius = (center_radius == 0) ? 1 : center_radius;

    GLfloat new_radius = std::max(radius, 0.0000001f);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<float> d(0, new_radius/2);

    GLfloat radius_multiplier;
    for (int i = 0; i < n; i++)
    {
        // radius_multiplier = (outer_only) ? 1 : random_number(0.0f, 1.0f);
        if (!outer_only)
        {
            new_radius = std::abs(d(gen));
        }
        glm::vec3 tmp_position = glm::sphericalRand(new_radius + center_radius) + offset;
        glm::vec3 tmp_velocity = this->sample_velocity(tmp_position, offset, min_velocity, max_velocity, is_spiral);
        GLfloat tmp_mass = random_number(min_mass, max_mass);

        this->particle_position.push_back(tmp_position);
        this->particle_velocity.push_back(tmp_velocity);
        this->particle_acceleration.push_back(glm::vec3(0.0f));
        this->particle_mass.push_back(tmp_mass);
    }

    this->n_particle += n;
    if (!outer_only)
    {
        this->setup_summary.append("Globular Cluster: " + std::to_string(n) + ' ' + this->format_string_vec3(offset) + ' ' + std::to_string(radius) + ' ' + std::to_string(center_radius) + " (" + std::to_string(min_mass) + ", " + std::to_string(max_mass) + ") " + "(" + std::to_string(min_velocity) + ", " + std::to_string(max_velocity) + ") " + std::to_string(is_spiral) + ' ' + std::to_string(outer_only) + "\n");
    }
}

void ParticleBuilder::spawn_sphere(GLuint n, glm::vec3 offset, GLfloat radius, GLfloat min_mass, GLfloat max_mass, GLfloat min_velocity, GLfloat max_velocity, bool is_spiral)
{
    this->spawn_globular_cluster(n, offset, 0, radius, min_mass, max_mass, min_velocity, max_velocity, is_spiral, 1);
    this->setup_summary.append("Sphere Surface: " + std::to_string(n) + ' ' + this->format_string_vec3(offset) + ' ' + std::to_string(radius) + ' ' + " (" + std::to_string(min_mass) + ", " + std::to_string(max_mass) + ") " + "(" + std::to_string(min_velocity) + ", " + std::to_string(max_velocity) + ") " + std::to_string(is_spiral) + "\n");
}

void ParticleBuilder::spawn_double_sphere(GLuint n, glm::vec3 offset, GLfloat radius, GLfloat center_radius, GLfloat min_mass, GLfloat max_mass, GLfloat min_velocity, GLfloat max_velocity, bool is_spiral)
{
    this->spawn_sphere((int)std::ceil(n / 2), offset, radius, min_mass, max_mass, min_velocity, max_velocity, is_spiral);
    this->spawn_sphere((int)std::floor(n / 2), offset, center_radius, min_mass, max_mass, min_velocity, max_velocity, is_spiral);
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

void ParticleBuilder::spawn_disc(GLuint n, glm::vec3 offset, GLfloat radius, GLfloat width, GLfloat min_mass, GLfloat max_mass, GLfloat min_velocity, GLfloat max_velocity, bool is_spiral, bool dense_center)
{
    GLfloat new_radius = std::max(radius, 0.0000001f);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<float> d(0, new_radius/2);

    for (int i = 0; i < n; i++)
    {
        if (dense_center)
        {
            new_radius = std::abs(d(gen));
        }
        glm::vec2 disc_pos = glm::diskRand(new_radius+ 1.0f);
        glm::vec3 tmp_position = glm::vec3(disc_pos.x, disc_pos.y, this->random_number(-width, width)) + offset;
        glm::vec3 tmp_velocity = this->sample_velocity(tmp_position, offset, min_velocity, max_velocity, is_spiral);
        GLfloat tmp_mass = random_number(min_mass, max_mass);

        this->particle_position.push_back(tmp_position);
        this->particle_velocity.push_back(tmp_velocity);
        this->particle_acceleration.push_back(glm::vec3(0.0f));
        this->particle_mass.push_back(tmp_mass);
    }

    this->n_particle += n;
    this->setup_summary.append("Disc: " + std::to_string(n) + ' ' + this->format_string_vec3(offset) + ' ' + std::to_string(radius) + ' ' + std::to_string(width) + " (" + std::to_string(min_mass) + ", " + std::to_string(max_mass) + ") " + "(" + std::to_string(min_velocity) + ", " + std::to_string(max_velocity) + ") " + std::to_string(is_spiral) + "\n");
}

std::string ParticleBuilder::get_summary()
{
    return "Total number of particles: " + std::to_string(this->n_particle) + "\n" + this->setup_summary;
}

std::string ParticleBuilder::format_string_vec3(glm::vec3 input)
{
    return "(" + std::to_string(input.x) + ", " + std::to_string(input.y) + ", " + std::to_string(input.z) + ")";
}