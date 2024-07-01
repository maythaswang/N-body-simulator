#include <GLCommon.h>
#include <Particle.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>

/**
 * @brief This simulator uses Particle-Particle method O(n^2)
 * 
 */
class Simulator
{
public:
    Simulator(GLfloat, GLfloat);

private:
    Particle *particles; 
    GLfloat gravitational_constant;
    GLfloat softening_factor;
    glm::vec3 calculate_force(Particle, Particle);
};