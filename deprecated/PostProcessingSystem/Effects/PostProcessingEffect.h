#ifndef POST_PROCESSING_EFFECT_H
#define EFFECT_H
#pragma once
#include <GLCommon.h>
#include <Shader/Shader.h>
#include <vector>

class PostProcessingEffect
{
public:
    PostProcessingEffect();
    virtual ~PostProcessingEffect() = 0;
    virtual void init(GLuint) = 0; // Maybe add multiple for texture id provided in the main PostProcessing pipeline
    virtual std::vector<GLuint> get_output_textures() const = 0;
    virtual void use_effect() = 0;
    virtual void terminate() = 0;

protected:
    std::vector<GLuint> output_textures();
};

#endif