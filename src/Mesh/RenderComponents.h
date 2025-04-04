#ifndef RENDER_COMPONENTS_H
#define RENDER_COMPONENTS_H
#pragma once
#include <GLCommon.h>
#include <vector>
#include <glm/glm.hpp>

struct RenderComponents
{
    GLuint VAO, VBO, EBO, n_vert, n_inds;
};

#endif