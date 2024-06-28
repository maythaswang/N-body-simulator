#include <SamplePolygon.h>

SamplePolygon::SamplePolygon()
{
}

void SamplePolygon::init_triangle(GLuint *VAO, GLuint *VBO, GLuint *EBO)
{
    const GLuint n_vert = 3;
    const GLuint n_inds = 1;

    GLfloat vert[n_vert][3] = {
        {-0.5f, -0.5f, 0.0f},
        {0.5f, -0.5f, 0.0f},
        {0.0f, 0.5f, 0.0f}};

    GLuint inds[1][3] = {{0, 1, 2}};
    glGenVertexArrays(1, VAO);
    glGenBuffers(1, VBO);
    glGenBuffers(1, EBO);

    glBindVertexArray(*VAO);

    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * n_vert * 3, &vert[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * n_inds * 3, &inds[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Unbind VAOs, VBOs, EBOs
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void SamplePolygon::init_cube(GLuint *VAO, GLuint *VBO, GLuint *EBO)
{
    const GLuint n_vert = 8;
    const GLuint n_inds = 12;

    GLfloat vertices[n_vert][3] = {
        {-0.5f, -0.5f, -0.5f},
        {-0.5f, -0.5f, 0.5f},
        {-0.5f, 0.5f, -0.5f},
        {-0.5f, 0.5f, 0.5f},
        {0.5f, 0.5f, 0.5f},
        {0.5f, -0.5f, 0.5f},
        {0.5f, 0.5f, -0.5f},
        {0.5f, -0.5f, -0.5f}};

    GLuint indices[n_inds][3] = {
        {0, 1, 2},
        {1, 2, 3},
        {4, 5, 6},
        {5, 6, 7},
        {1, 5, 0},
        {0, 5, 7},
        {0, 2, 7},
        {2, 6, 7},
        {3, 2, 6},
        {6, 3, 4},
        {1, 5, 3},
        {3, 5, 4}};

    glGenVertexArrays(1, VAO);
    glGenBuffers(1, VBO);
    glGenBuffers(1, EBO);

    glBindVertexArray(*VAO);

    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * n_vert * 3, &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * n_inds * 3, &indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Unbind VAOs, VBOs, EBOs
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
