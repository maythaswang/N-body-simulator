#include "MeshBuilder.h"

MeshBuilder::MeshBuilder()
{
}

MeshBuilder::~MeshBuilder() {}

RenderComponents MeshBuilder::build_sphere(GLfloat radius, GLfloat sector_count, GLfloat stack_count)
{
    RenderComponents render_components;

    // constants
    GLfloat PI = 3.14159265;

    // storage for required data
    std::vector<glm::vec3> vertices;
    std::vector<glm::ivec3> indices;

    // Variables for building sphere
    GLfloat x, y, z, xy;
    GLfloat sector_step = 2 * PI / sector_count;
    GLfloat stack_step = PI / stack_count;
    GLfloat sector_angle, stack_angle;

    // Build vertices
    for (int i = 0; i <= stack_count; ++i)
    {
        stack_angle = PI / 2 - i * stack_step; // starting from pi/2 to -pi/2
        xy = radius * cosf(stack_angle);       // r * cos(u)
        z = radius * sinf(stack_angle);        // r * sin(u)

        // add (sectorCount+1) vertices per stack
        // first and last vertices have same position
        for (int j = 0; j <= sector_count; ++j)
        {
            sector_angle = j * sector_step; // starting from 0 to 2pi
            x = xy * cosf(sector_angle);    // r * cos(u) * cos(v)
            y = xy * sinf(sector_angle);    // r * cos(u) * sin(v)

            vertices.push_back(glm::vec3(x, y, z));
        }
    }

    // Build Indices
    int k1, k2;
    for (int i = 0; i < stack_count; ++i)
    {
        k1 = i * (sector_count + 1); // beginning of current stack
        k2 = k1 + sector_count + 1;  // beginning of next stack

        for (int j = 0; j < sector_count; ++j, ++k1, ++k2)
        {
            // 2 triangles per sector excluding first and last stacks
            // k1 => k2 => k1+1
            if (i != 0)
            {
                indices.push_back(glm::vec3(k1, k2, k1 + 1));
            }

            // k1+1 => k2 => k2+1
            if (i != (stack_count - 1))
            {
                indices.push_back(glm::vec3(k1 + 1, k2, k2 + 1));
            }
        }
    }
    this->build_render_components(&render_components, vertices, indices);
    
    return render_components;
    // this->generate_sphere_indices(&mesh, sector_count, stack_count);
    // return mesh;
}

void MeshBuilder::build_render_components(RenderComponents *render_components, std::vector<glm::vec3> vertices, std::vector<glm::ivec3> indices)
{
    // Initialize
    glGenVertexArrays(1, &render_components->VAO);
    glGenBuffers(1, &render_components->VBO);
    glGenBuffers(1, &render_components->EBO);

    glBindVertexArray(render_components->VAO);
    glEnableVertexAttribArray(0);

    // VBO
    glBindBuffer(GL_ARRAY_BUFFER, render_components->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size() * 3, &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);

    // EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, render_components->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size() * 3, &indices[0], GL_STATIC_DRAW);

    // Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

// void MeshBuilder::generate_sphere_indices(RenderingComponents *mesh, GLuint sector_count, GLuint stack_count)
// {

//     // Copy the indices into the mesh struct
//     mesh->indices.resize(indices.size());
//     std::copy(indices.begin(), indices.end(), mesh->indices.begin());
// }