#include <Simulator.h>

Simulator::Simulator(GLfloat n_particle, GLfloat gravitational_constant, GLfloat softening_factor, GLfloat timestep_size, SimulatorIntegrator integrator)
{
    this->gravitational_constant = gravitational_constant;
    this->softening_factor = softening_factor;
    this->timestep_size = timestep_size;
    this->current_step = 0;
    this->running_state = 0;
    this->integrator = integrator;
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

    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * this->n_particle * 3, &this->particle_position[0]);

    this->current_step += 1;
}

glm::vec3 Simulator::calculate_acceleration(uint32_t current, uint32_t other)
{
    return glm::vec3(0.0f);
}

void Simulator::update_position_euler()
{
    // Do nothing
}

void Simulator::update_position_velocity_verlet()
{
    // Do Nothing
}

void Simulator::initialize_particles(GLuint *VAO, GLuint *VBO)
{
    glGenVertexArrays(1, VAO);
    glGenBuffers(1, VBO);

    glBindVertexArray(*VAO);
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * this->n_particle * 3, &this->particle_position[0], GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    this->VAO = VAO;
    this->VBO = VBO;
}

void Simulator::load_particles(GLuint n, std::vector<glm::vec3> position, std::vector<glm::vec3> velocity, std::vector<glm::vec3> previous_acceleration, std::vector<GLfloat> mass)
{
    this->n_particle = n;
    this->particle_position = position;
    this->particle_velocity = velocity;
    this->particle_previous_acceleration = previous_acceleration;
    this->particle_mass = mass;

    this->particle_acceleration.resize(this->n_particle);
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