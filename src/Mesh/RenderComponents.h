#ifndef H_RENDER_COMPONENTS
#define H_RENDER_COMPONENTS
#pragma once
#include <GLCommon.h>
#include <vector>
#include <glm/glm.hpp>

struct RenderComponents
{
    GLuint VAO, VBO, EBO, n_vert, n_inds;
};

#endif