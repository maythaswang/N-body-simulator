#include <Particle.h>
#include <iostream>

Particle::Particle(glm::vec3 position)
{
    this->position = position;
    this->velocity = glm::vec3();
    this->acceleration = glm::vec3();
}

void Particle::print_information()
{
    std::cout << "position: " << this->position.x << ", " << this->position.y << ", " << this->position.z << std::endl;
    std::cout << "velocity: " << this->velocity.x << ", " << this->velocity.y << ", " << this->velocity.z << std::endl;
    std::cout << "acceleration: " << this->acceleration.x << ", " << this->acceleration.y << ", " << this->acceleration.z << std::endl;
}

GLfloat Particle::get_mass()
{
    return this->mass;
}

glm::vec3 Particle::get_position()
{
    return this->position;
}

glm::vec3 Particle::get_velocity()
{
    return this->velocity;
}

glm::vec3 Particle::get_acceleration()
{

    return this->acceleration;
}

void Particle::set_mass(GLfloat mass)
{
    this->mass = mass;
}

void Particle::set_position(glm::vec3 position)
{
    this->position = position;
}

void Particle::set_velocity(glm::vec3 velocity)
{
    this->velocity = velocity;
}

void Particle::set_acceleration(glm::vec3 acceleration)
{
    this->acceleration = acceleration;
}