#ifndef H_MESH
#define H_MESH
#pragma once 
#include <GLCommon.h>
#include <vector>
#include <glm/glm.hpp>

struct Mesh{ 
    std::vector<glm::vec4> vertices;
    std::vector<glm::vec4> indices;
};

#endif