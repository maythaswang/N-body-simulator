#include "Bloom.h"
#include <iostream>

Bloom::Bloom(GLfloat screen_w, GLfloat screen_h)
{
    this->screen_w = screen_w;
    this->screen_h = screen_h;
    this->enabled = false;
    this->init();
    this->generate_rectangle();
}

Bloom::~Bloom()
{
}

void Bloom::init()
{
    // Stage 0
    // ---------------------------------------------------

    // Render FrameBuffer
    glGenFramebuffers(1, &this->render_FBO);
    // glBindFramebuffer(GL_FRAMEBUFFER, this->render_FBO);

    // Color texture
    glGenTextures(1, &this->color_texture);
    this->setup_texture(this->color_texture);

    glGenTextures(1, &this->color_threshold_texture);
    this->setup_texture(this->color_threshold_texture);

    // Stage 1
    // ---------------------------------------------------
    this->gaussian_blur_shader = Shader();

    glGenTextures(2, this->pingpong_texture);
    this->setup_texture(this->pingpong_texture[0]);
    this->setup_texture(this->pingpong_texture[1]);

    // Stage 2
    // ---------------------------------------------------
    this->bloom_combine_shader = Shader();

    glGenTextures(1, &this->bloom_combine_texture);
    this->setup_texture(this->bloom_combine_texture);

    // Stage 3
    // ---------------------------------------------------
    this->draw_final_shader = Shader();
    GLuint draw_final_shader_vs = draw_final_shader.compile_shader("./shader_source/bloom/draw_final_texture.vs", GL_VERTEX_SHADER);
    GLuint draw_final_shader_fs = draw_final_shader.compile_shader("./shader_source/bloom/draw_final_texture.fs", GL_FRAGMENT_SHADER);
    draw_final_shader.link_shader(draw_final_shader_vs);
    draw_final_shader.link_shader(draw_final_shader_fs);
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
    // color buffer and depth buffer is not cleared here
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST);
}

void Bloom::resize(GLfloat screen_w, GLfloat screen_h)
{
    this->screen_w = screen_w;
    this->screen_h = screen_h;

    // Do this for all textures
    // glBindTexture(GL_TEXTURE_2D, this->color_texture);
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, this->screen_w, this->screen_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

    // glBindTexture(GL_TEXTURE_2D, this->color_threshold_texture);
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, this->screen_w, this->screen_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

    // glBindTexture(GL_TEXTURE_2D, this->pingpong_texture[0]);
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, this->screen_w, this->screen_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

    // glBindTexture(GL_TEXTURE_2D, this->pingpong_texture[1]);
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, this->screen_w, this->screen_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glBindTexture(GL_TEXTURE_2D, this->bloom_combine_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, this->screen_w, this->screen_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
}

void Bloom::generate_rectangle()
{
    GLfloat vertices[] = {
        //  Coords   // texCoords
        1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

        1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f, 0.0f, 1.0f};

    // Generate VAO
    glGenVertexArrays(1, &this->rect_VAO);
    glBindVertexArray(this->rect_VAO);

    // Generate VBO
    glGenBuffers(1, &this->rect_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->rect_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));

    // unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Bloom::draw_result()
{
    this->draw_final_shader.use();
    glBindVertexArray(this->rect_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void Bloom::set_enabled(bool enabled){
    this->enabled = enabled;
}

bool Bloom::get_enabled(){
    return this->enabled;
}