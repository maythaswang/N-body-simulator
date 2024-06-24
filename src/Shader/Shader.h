#pragma once
#include <string>
#include <GLAD/glad.h>

class Shader
{
public:
    /**
     * @brief Construct a new Shader object
     *
     */
    Shader() {}

    /**
     * @brief Create a Shader according to the shader type specified.
     * For instance, you can create fragment and vertex shader.
     *
     * @param file_name
     * @param shaderType
     * @return status of shader creation
     */
    GLuint CompileShader(std::string file_name, GLenum shaderType);

private:
    uint64_t shader_id;

    /**
     * @brief Read the shader file
     * 
     * @param file_name 
     * @return const char* 
     */
    const char *ReadShaderFile(std::string file_name);
};