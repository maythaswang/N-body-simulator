#ifndef BLOOM_H
#define BLOOM_H
#pragma once
#include <GLCommon.h>
#include <Shader/Shader.h>

class Bloom
{
public:
    Bloom(GLfloat screen_h, GLfloat screen_w);
    ~Bloom();

    /**
     * @brief Bind to render framebuffer for post processing
     *
     */
    void bind_render_FBO();

    /**
     * @brief Bind to Framebuffer to the default FBO to render to screen
     *
     */
    void bind_default_FBO();

    void apply_effect();

    /**
     * @brief Render final result and the triangle
     *
     */
    void draw_result();

    /**
     * @brief Use to resize screen when the callback is triggered
     *
     * @param screen_w
     * @param screen_h
     */
    void resize(GLfloat screen_w, GLfloat screen_h);

    bool get_enabled();

    void set_enabled(bool);

    void terminate();
    
    void set_exposure(GLfloat exposure);
    void set_gamma(GLfloat gamma);
    void set_blur_intensity(GLfloat blur_intensity);
    GLfloat get_exposure();
    GLfloat get_gamma();
    GLfloat get_blur_intensity();
    void reset_default();
private:
    bool enabled;

    // Default values
    GLfloat default_exposure = 2.0;
    GLfloat default_gamma = 2.2;
    GLfloat default_blur_intensity = 0.4;
    GLfloat exposure, gamma, blur_intensity;

    // Rectangle for drawing to screen
    GLuint rect_VAO, rect_VBO;

    // Screen configuration
    GLfloat screen_w, screen_h;

    // Stage 0: get the rendered color texture
    GLuint render_FBO; // Store result from rendering stage (ID 0)
    GLuint render_depth_buffer;
    GLuint color_texture, color_threshold_texture;

    // Stage 1: 2-pass gaussian blur
    GLuint pingpong_FBO[2];
    GLuint pingpong_texture[2];
    Shader gaussian_blur_shader;

    // Stage 2: Combine color and 2-pass gaussian blur
    Shader bloom_combine_shader;

    /**
     * @brief Initialize FBOs and textures
     * @note maybe add like bools for checking which Buffers are required.
     *
     */
    void init();

    /**
     * @brief Setup value of the new texture
     *
     * @param tex_id
     */
    void setup_texture(GLuint tex_id);

    /**
     * @brief Create rectangle mesh for drawing texture to
     *
     */
    void generate_rectangle();

    bool check_FBO();

};

#endif