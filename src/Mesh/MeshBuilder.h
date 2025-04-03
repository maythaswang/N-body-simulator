#ifndef H_MESH_BUILDER
#define H_MESH_BUILDER
#include <GLCommon.h>
#include <vector>
#include <glm/glm.hpp>

/**
 * @brief TBH im doing this part just because I wanted to try my hand on gpu instancing lol....
 * The implementation for sphere is fully based from songho.ca so please check it out if you are
 * interested for further information!!! :)
 */

struct RenderComponents
{
    GLuint VAO, VBO, EBO; 
};

/**
 * @brief Build meshes (this time only sphere lol)
 *
 */
class MeshBuilder
{
public:
    MeshBuilder();
    ~MeshBuilder();

    /**
     * @brief Create Sphere
     * @note This implementation is from here https://www.songho.ca/opengl/gl_sphere.html#sphere
     * @param radius radius of sphere
     * @param sector_count longitude
     * @param stack_count latitude
     * @return Mesh object storing vertices and indices
     */
    RenderComponents build_sphere(GLfloat radius, GLfloat sector_count, GLfloat stack_count);

    // /**
    //  * @brief generate indices for sphere
    //  *
    //  * @param mesh Mesh struct
    //  * @param sector_count longitude
    //  * @param stack_count latitude
    //  */
    // void generate_sphere_indices(RenderingComponents *, GLuint sector_count, GLuint stack_count);

private:
    /**
     * @brief Build render components based on vertices and indices (this is only for this sphere so its very limited)
     *
     * @param render_components
     * @param vertices
     * @param indices
     */
    void build_render_components(RenderComponents *render_components, std::vector<glm::vec3> vertices, std::vector<glm::ivec3> indices);
};
#endif