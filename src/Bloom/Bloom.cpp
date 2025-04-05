#include "Bloom.h"

Bloom::Bloom(GLfloat screen_w, GLfloat screen_h)
{
    this->screen_w = screen_w;
    this->screen_h = screen_h;
    this->init();
}

Bloom::~Bloom()
{
}

void Bloom::init()
{
    // Render FrameBuffer
    glGenFramebuffers(1, &this->render_FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, this->render_FBO);

    // Color texture
    glGenTextures(1, &this->color_texture);
    this->setup_texture(this->color_texture);

    // Output FrameBuffer
    glGenFramebuffers(1, &this->output_FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, this->output_FBO);

    // Output texture
    glGenTextures(1, &this->output_texture);
    this->setup_texture(this->output_texture);
}

void Bloom::setup_texture(GLuint tex_id)
{
    // Generate image texture to store result
    glBindTexture(GL_TEXTURE_2D, tex_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, this->screen_w, this->screen_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // attach texture
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex_id, 0);
}

void Bloom::bind_render_FBO()
{
    glBindFramebuffer(GL_FRAMEBUFFER, this->render_FBO);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glEnable(GL_DEPTH_TEST);
}

void Bloom::bind_default_FBO()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST);
}

void Bloom::resize(GLfloat screen_w, GLfloat screen_h)
{
    this->screen_w = screen_w;
    this->screen_h = screen_h;

    glBindTexture(GL_TEXTURE_2D, this->color_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, this->screen_w, this->screen_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

    glBindTexture(GL_TEXTURE_2D, this->output_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, this->screen_w, this->screen_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
}

void Bloom::generate_rectangle()
{
    GLfloat rectangleVertices[] = {
        //  Coords   // texCoords
        1.0f, -1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f, 0.0f,
        -1.0f, 1.0f, 0.0f, 1.0f,

        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f, 1.0f};

    // Generate VAO
    glGenVertexArrays(1, &this->rect_VAO);
    glBindVertexArray(this->rect_VAO);

    // Generate VBO
    glGenBuffers(1, &this->rect_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->rect_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), &rectangleVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void *)(2 * sizeof(GLfloat)));

    // unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Bloom::draw_result()
{
    glBindVertexArray(this->rect_VAO);
    // TODO: DRAW
    glBindVertexArray(0);
}