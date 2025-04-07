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
    // GLuint add_effect(); // TODO: return effect ID and take in the effect pointers
    // void apply_effect();

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

private:
    bool enabled;

    // Rectangle for drawing to screen
    GLuint rect_VAO, rect_VBO;

    // Screen configuration
    GLfloat screen_w, screen_h;

    // Stage 0: get the rendered color texture
    GLuint render_FBO; // Store result from rendering stage (ID 0)
    GLuint color_texture, color_threshold_texture;

    // Stage 1: 2-pass gaussian blur
    GLuint pingpong_FBO[2];
    GLuint pingpong_texture[2];
    Shader gaussian_blur_shader;

    // Stage 2: Combine color and 2-pass gaussian blur
    GLuint bloom_combine_FBO;
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