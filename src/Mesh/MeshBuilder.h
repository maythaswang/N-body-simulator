#ifndef H_MESH_BUILDER
#define H_MESH_BUILDER
#include "Mesh.h"

class MeshBuilder
{
public:
    MeshBuilder();
    ~MeshBuilder();
    Mesh init_sphere(GLfloat radius, GLfloat sector_count, GLfloat stack_count);


};
#endif