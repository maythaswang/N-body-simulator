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
    terminate();
}

void Bloom::init()
{
    GLenum fbo_status;
    bool init_success = 1;

    // Stage 0
    // ---------------------------------------------------

    // Render FrameBuffer
    glGenFramebuffers(1, &this->render_FBO);

    // Color textures
    glGenTextures(1, &this->color_texture);
    this->setup_texture(this->color_texture);
    glGenTextures(1, &this->color_threshold_texture);
    this->setup_texture(this->color_threshold_texture);

    // Bind texture to FBO
    glBindFramebuffer(GL_FRAMEBUFFER, this->render_FBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->color_texture, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, this->color_threshold_texture, 0);

    // use 2 attachment for this buffer
    GLuint attachments[2] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
    glDrawBuffers(2, attachments);

    glGenRenderbuffers(1, &this->render_depth_buffer);
    glBindRenderbuffer(GL_RENDERBUFFER, this->render_depth_buffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, this->screen_w, this->screen_h);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, this->render_depth_buffer);

    glDepthFunc(GL_LESS);

    init_success &= this->check_FBO();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Stage 1
    // ---------------------------------------------------

    // Pingpong 2 pass gaussian FBO
    glGenFramebuffers(2, this->pingpong_FBO);

    // Gen textures
    glGenTextures(2, this->pingpong_texture);
    this->setup_texture(this->pingpong_texture[0]);
    this->setup_texture(this->pingpong_texture[1]);

    // Bind texture to FBO
    glBindFramebuffer(GL_FRAMEBUFFER, this->pingpong_FBO[0]);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->pingpong_texture[0], 0);
    init_success &= this->check_FBO();

    glBindFramebuffer(GL_FRAMEBUFFER, this->pingpong_FBO[1]);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->pingpong_texture[1], 0);
    init_success &= this->check_FBO();

    // Prepare shader
    this->gaussian_blur_shader = Shader();
    GLuint gaussian_blur_shader_vs = gaussian_blur_shader.compile_shader("./shader_source/bloom/gaussian_blur.vs", GL_VERTEX_SHADER);
    GLuint gaussian_blur_shader_fs = gaussian_blur_shader.compile_shader("./shader_source/bloom/gaussian_blur.fs", GL_FRAGMENT_SHADER);
    this->gaussian_blur_shader.link_shader(gaussian_blur_shader_vs);
    this->gaussian_blur_shader.link_shader(gaussian_blur_shader_fs);

    this->gaussian_blur_shader.use();
    this->gaussian_blur_shader.set_int("u_prev_texture", 0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    // Stage 2
    // ---------------------------------------------------

    // Prepare shader
    this->bloom_combine_shader = Shader();
    GLuint bloom_combine_shader_vs = bloom_combine_shader.compile_shader("./shader_source/bloom/bloom_combine.vs", GL_VERTEX_SHADER);
    GLuint bloom_combine_shader_fs = bloom_combine_shader.compile_shader("./shader_source/bloom/bloom_combine.fs", GL_FRAGMENT_SHADER);
    bloom_combine_shader.link_shader(bloom_combine_shader_vs);
    bloom_combine_shader.link_shader(bloom_combine_shader_fs);

    // Pre-set uniforms
    bloom_combine_shader.use();
    bloom_combine_shader.set_int("u_color_texture", 0);
    bloom_combine_shader.set_int("u_blur_texture", 1);

    this->reset_default();
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

void Bloom::apply_effect()
{
    // glDisable(GL_DEPTH_TEST);
    bool is_vertical = true, initial_run = true;
    int blur_intensity = 8;
    this->gaussian_blur_shader.use();

    for (int i = 0; i < blur_intensity; i++)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, this->pingpong_FBO[!is_vertical]);
        glBindVertexArray(this->rect_VAO);

        this->gaussian_blur_shader.set_bool("is_horizontal", !is_vertical);

        glActiveTexture(GL_TEXTURE0);
        if (initial_run)
        {
            glBindTexture(GL_TEXTURE_2D, this->color_threshold_texture);
            initial_run = false;
        }
        else
        {
            glBindTexture(GL_TEXTURE_2D, this->pingpong_texture[is_vertical]);
        }

        glDisable(GL_DEPTH_TEST);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        is_vertical = !is_vertical;
    }

    glBindVertexArray(0);
}

void Bloom::bind_render_FBO()
{
    // Stage 0
    glBindFramebuffer(GL_FRAMEBUFFER, this->render_FBO);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glEnable(GL_DEPTH_TEST);
}

void Bloom::bind_default_FBO()
{
    // color buffer and depth buffer is not cleared here
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glDisable(GL_DEPTH_TEST);
}

void Bloom::resize(GLfloat screen_w, GLfloat screen_h)
{
    this->screen_w = screen_w;
    this->screen_h = screen_h;

    // Do this for all textures
    glBindTexture(GL_TEXTURE_2D, this->color_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, this->screen_w, this->screen_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

    glBindTexture(GL_TEXTURE_2D, this->color_threshold_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, this->screen_w, this->screen_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

    glBindTexture(GL_TEXTURE_2D, this->pingpong_texture[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, this->screen_w, this->screen_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

    glBindTexture(GL_TEXTURE_2D, this->pingpong_texture[1]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, this->screen_w, this->screen_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

    glBindRenderbuffer(GL_RENDERBUFFER, this->render_depth_buffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, this->screen_w, this->screen_h);
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
    this->bloom_combine_shader.use();
    glBindVertexArray(this->rect_VAO);

    // Bind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->color_texture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, this->pingpong_texture[0]);

    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void Bloom::set_enabled(bool enabled)
{
    this->enabled = enabled;
}

bool Bloom::get_enabled()
{
    return this->enabled;
}

bool Bloom::check_FBO()
{
    bool failed = glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE;
    if (failed)
        std::cout << "Framebuffer not complete!" << std::endl;
    return !failed;
}

void Bloom::terminate()
{
    // Rectangle
    glDeleteVertexArrays(1, &this->rect_VAO);
    glDeleteBuffers(1, &this->rect_VBO);

    // FBO
    glDeleteFramebuffers(1, &this->render_FBO);
    glDeleteFramebuffers(2, this->pingpong_FBO);

    // RBO
    glDeleteRenderbuffers(1, &this->render_depth_buffer);

    // Textures
    glDeleteTextures(1, &this->color_texture);
    glDeleteTextures(1, &this->color_threshold_texture);
    glDeleteTextures(2, this->pingpong_texture);

    // Shaders
    this->gaussian_blur_shader.delete_shader();
    this->bloom_combine_shader.delete_shader();
}

void Bloom::set_gamma(GLfloat gamma)
{
    this->bloom_combine_shader.use();
    this->bloom_combine_shader.set_float("u_gamma", gamma);
    this->gamma = gamma;
}

void Bloom::set_exposure(GLfloat exposure)
{
    this->bloom_combine_shader.use();
    this->bloom_combine_shader.set_float("u_exposure", exposure);
    this->exposure = exposure;
}

void Bloom::set_blur_intensity(GLfloat blur_intensity)
{
    this->bloom_combine_shader.use();
    this->bloom_combine_shader.set_float("u_blur_intensity", blur_intensity);
    this->blur_intensity = blur_intensity;
}



void Bloom::reset_default()
{
    this->bloom_combine_shader.use();
    this->bloom_combine_shader.set_float("u_gamma", default_gamma);
    this->bloom_combine_shader.set_float("u_exposure", default_exposure);
    this->bloom_combine_shader.set_float("u_blur_intensity", default_blur_intensity);
    this->exposure = default_exposure;
    this->gamma = default_gamma;
    this->blur_intensity = default_blur_intensity;
}

GLfloat Bloom::get_gamma(){
    return this->gamma;
}

GLfloat Bloom::get_exposure(){
    return this->exposure;
}

GLfloat Bloom::get_blur_intensity(){
    return this->blur_intensity;
}

