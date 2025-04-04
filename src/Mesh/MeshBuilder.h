#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H
#include "RenderComponents.h"

/**
 * @brief Build meshes (this time only sphere lol)
 * @note TBH im doing this part just because I wanted to try my hand on gpu instancing lol....
 * The implementation for sphere is fully based from songho.ca so please check it out if you are
 * interested for further information!!! :)
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