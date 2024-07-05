#include <Simulator.h>
#include <iostream>


Simulator::Simulator(GLfloat n_particle, GLfloat gravitational_constant, GLfloat softening_factor, GLfloat timestep_size)
{
    this->gravitational_constant = gravitational_constant;
    this->softening_factor = softening_factor;
    this->timestep_size = timestep_size;
    this->current_step = 0;
    this->running_state = 0;
}

glm::vec3 Simulator::calculate_acceleration(uint32_t current, uint32_t other)
{
    glm::vec3 temp_distance = this->particle_position[current] - this->particle_position[other];
    
    // Since we did not handle collision, this will prevent 0 division when calculating direction (as inaccurate as it is).
    if (temp_distance == glm::vec3(0.0f)){ 
        return glm::vec3(0.0f);
    }

    glm::vec3 direction = -glm::normalize(temp_distance);
    GLfloat sq_distance = glm::dot(temp_distance, temp_distance);
    GLfloat sq_soften = std::pow(this->softening_factor, 2);
    return (this->particle_mass[other] / std::sqrt(sq_distance + sq_soften)) * direction;
}

void Simulator::next_step()
{
    // TODO: Create Enumerator for integrators and make them swappable
    // this->update_position_euler();
    this->update_position_velocity_verlet();

    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * this->n_particle * 3, &this->particle_position[0]);

    this->current_step +=1;
}

void Simulator::update_position_euler()
{
    glm::vec3 tmp_acceleration;
    std::fill(this->particle_acceleration.begin(), this->particle_acceleration.end(), glm::vec3(0.0f));

    // Update Acceleration
    for (int i = 0; i < this->n_particle; i++)
    {
        for (int j = i + 1; j < this->n_particle; j++)
        {
            tmp_acceleration = this->calculate_acceleration(i, j);
            this->particle_acceleration[i] += tmp_acceleration;
            this->particle_acceleration[j] -= tmp_acceleration;
        }
    }

    for(int i = 0; i < this->n_particle; i++){
        // Update Velocity
        this->particle_velocity[i] += this->particle_acceleration[i] * this->timestep_size * this->gravitational_constant;

        // Update Position
        this->particle_position[i] += this->particle_velocity[i] * this->timestep_size;
    }
}

void Simulator::update_position_velocity_verlet(){

    glm::vec3 tmp_acceleration;
    std::fill(this->particle_acceleration.begin(), this->particle_acceleration.end(), glm::vec3(0.0f));

    for (int i = 0; i < this->n_particle; i++){
        // Update velocity by 1/2 timestep
        this->particle_velocity[i] += this->particle_previous_acceleration[i] * this->timestep_size * (GLfloat) 0.5 * this->gravitational_constant;

        // Update position by 1 step
        this->particle_position[i] += this->particle_velocity[i] * this->timestep_size;
    }
    
    // Update Acceleration by 1 step
    for (int i = 0; i < this->n_particle; i++)
    {
        for (int j = i + 1; j < this->n_particle; j++)
        {
            tmp_acceleration = this->calculate_acceleration(i, j);
            this->particle_acceleration[i] += tmp_acceleration;
            this->particle_acceleration[j] -= tmp_acceleration;
        }
        
        // Update Velocity by 1 step
        this->particle_velocity[i] += particle_acceleration[i] * this->timestep_size * (GLfloat) 0.5 * this->gravitational_constant;
    }

    // Copy next step acceleration for next iteration
    std::copy(this->particle_previous_acceleration.begin(), this->particle_previous_acceleration.end(), std::back_inserter(particle_acceleration));  
}

void Simulator::initialize_particles(GLuint *VAO, GLuint *VBO)
{
    glGenVertexArrays(1, VAO);
    glGenBuffers(1, VBO);

    glBindVertexArray(*VAO);
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * this->n_particle * 3, &this->particle_position[0], GL_STREAM_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    this->VAO = VAO;
    this->VBO = VBO;
}

void Simulator::load_particles(GLuint n, std::vector<glm::vec3> position, std::vector<glm::vec3> velocity, std::vector<glm::vec3> previous_acceleration, std::vector<GLfloat> mass){
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

GLuint Simulator::get_current_step(){
    return this->current_step;
}

GLfloat Simulator::get_timestep_size(){
    return this->timestep_size;
}

GLuint Simulator::get_n_particle(){
    return this->n_particle;
}