#ifndef PP_TEXTURE_MANAGER_H
#define PP_TEXTURE_MANAGER_H
#pragma once
#include <GLCommon.h>
#include <vector>
#include <unordered_map>

/**
 * @brief Manage each effect texture according to its ID, users can fetch the required shader based on the ID provided.
 *
 */

class PPTextureManager
{
public:
    PPTextureManager();
    ~PPTextureManager();
    void add_texture_ids(std::vector<GLuint>); 
    GLuint fetch_texture_ids(GLuint effect_id, GLuint texture_id); // eg: 0, 0 = color texture from render
private: 
    std::unordered_map<GLuint, std::vector<GLuint>> texture_table;
};

#endif