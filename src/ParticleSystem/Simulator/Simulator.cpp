#include "Simulator.h"
// TODO: Implement Save/Load (both setup only and current state)

Simulator::Simulator(GLfloat n_particle, GLfloat gravitational_constant, GLfloat softening_factor, GLfloat timestep_size, SimulatorIntegrator integrator)
{
    this->gravitational_constant = gravitational_constant;
    this->softening_factor = softening_factor;
    this->timestep_size = timestep_size;
    this->current_step = 0;
    this->running_state = 0;
    this->integrator = integrator;
    this->setup_log = "";
}

void Simulator::next_step()
{
    switch (this->integrator)
    {
    case INTEGRATOR_EULER:
        this->update_position_euler();
        break;
    case INTEGRATOR_VELOCITY_VERLET:
        this->update_position_velocity_verlet();
        break;
    default:
        this->update_position_velocity_verlet();
        break;
    }

    this->current_step += 1;
}

void Simulator::update_position_euler()
{
    // Do Nothing
}

void Simulator::update_position_velocity_verlet()
{
    // Do Nothing
}

void Simulator::load_particles(GLuint n, std::vector<glm::vec4> position, std::vector<glm::vec4> velocity, std::vector<glm::vec4> previous_acceleration, std::vector<GLfloat> mass)
{
    // Do Nothing
}

bool Simulator::get_running_state()
{
    return this->running_state;
}
void Simulator::set_running_state(bool running_state)
{
    this->running_state = running_state;
}

GLuint Simulator::get_current_step()
{
    return this->current_step;
}

GLfloat Simulator::get_timestep_size()
{
    return this->timestep_size;
}

GLuint Simulator::get_n_particle()
{
    return this->n_particle;
}

void Simulator::terminate()
{
    // Do nothing
}

std::string Simulator::get_setup_log()
{
    return this->setup_log;
}

void Simulator::append_setup_log(std::string input)
{
    this->setup_log.append(input);
}