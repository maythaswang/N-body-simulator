#ifndef BLOOM_H
#define BLOOM_H
#pragma once
#include <GLCommon.h>
#include <Shader/Shader.h>

/**
 * @brief This class basically allows top-down for applying post-processing shader, the final shader will have to summarize the generated textures and 
 * @warning ACTUALLY YOU KNOW WHAT, THIS DOESN'T REALLY WORK.... I'LL JUST LIE DOWN AND CRY
 * @note For this to actually work, this will require a proper texture management system (global?) that stores intermediate shader texture from each stages
 * @note Allow building only once
 */

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

    /**
     * @brief Render final result and the triangle
     * 
     */
    void draw_result();

    /**
     * @brief Build PostProcessor
     * @warning Can be done only once
     */
    void build_post_processor();
        
private: 
    GLuint rect_VAO, rect_VBO; // Rectangle for result screen
    GLuint render_FBO, color_texture; // Store result from rendering stage (ID 0)
    GLuint output_FBO, output_texture; // Final result after post processing (ID n)
    // We'll ignore depth and stencil for now
    // Maybe will need to store some effects then run top down 

    GLfloat screen_h, screen_w;

    /**
     * @brief Initialize FBOs and textures
     * @note maybe add like bools for checking which Buffers are required.
     * 
     */
    void init();
    void setup_texture(GLuint tex_id);
    void generate_rectangle();
    
    void resize(GLfloat screen_w, GLfloat screen_h);

};

#endif