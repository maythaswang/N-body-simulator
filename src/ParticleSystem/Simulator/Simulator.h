#include <GLCommon.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/random.hpp>
#include <math.h>
#include <vector>

/**
 * @brief This simulator is implemented using Sequential Particle-Particle method O(n^2) on CPU
 *
 */
class Simulator
{
public:
    /**
     * @brief Construct a new Simulator:: Simulator object
     *
     * @param n_particle
     * @param gravitational_constat
     * @param softening_factor
     * @param timestep_size
     */
    Simulator(GLfloat, GLfloat, GLfloat, GLfloat);

    /**
     * @brief Calculate the next step of the simulation
     *
     */
    void next_step();

    void initialize_particles(GLuint *, GLuint *);

private:
    std::vector<glm::vec3> particle_position;
    std::vector<glm::vec3> particle_velocity;
    std::vector<glm::vec3> particle_acceleration;
    std::vector<GLfloat> particle_mass;
    GLfloat gravitational_constant;
    GLfloat softening_factor;
    GLfloat timestep_size;
    GLfloat current_time;
    GLfloat n_particle;
    GLuint *VAO;
    GLuint *VBO;

    /**
     * @brief Calculate acceleration between the two particles
     *
     * @note F = Gmm/r^2 * -r/||r||, F = ma
     * @note ma = Gmm/r^2 * -r/||r||
     * @note a = G ∑ m/r^2 * -r/||r||
     * @param current
     * @param other
     * @return acceleration of the particle "current" based on force being exerted from the particle "other"
     */
    glm::vec3 calculate_acceleration(uint32_t, uint32_t);

    /**
     * @brief Update the position of each particle using euler method
     * @note v = dx/dt, a = dv/dt
     * @note dx = v * dt, dv = a * dt
     * @note x_n+1 = x_n + h * dx, v_n+1 = v_n + h * dv
     */
    void update_position_euler();

    
    void update_position_velocity_verlet(); //TODO: Implement this.

    void spawn_globular_cluster(GLfloat, GLfloat, GLfloat);
    void spawn_sphere(GLfloat, GLfloat, GLfloat);
};