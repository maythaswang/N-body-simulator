#pragma once
#include <string>
#include <GLAD/glad.h>

// TODO: Maybe rename this class .... 
class Shader
{
public:
    /**
     * @brief Construct a new Shader object
     *
     */
    Shader() {
        has_program = false;
    }

    /**
     * @brief Create a Shader according to the shader type specified.
     * For instance, you can create fragment and vertex shader.
     *
     * @param file_name
     * @param shaderType
     * @return status of shader creation
     */
    GLuint CompileShader(std::string file_name, GLenum shaderType);

    /**
     * @brief Link shader that has been built by CompileShader. 
     * @note The shader that has been inputted will be deleted after this function call.
     * 
     * @param shader 
     */
    void LinkShader(GLuint shader);

    /**
     * @brief Get the ShaderID
     * 
     * @return GLuint 
     */
    GLuint GetShaderID();
    
    /**
     * @brief Delete the shader program
     * 
     */
    void DeleteShader();

private:
    GLuint shader_id;
    bool has_program; 

    /**
     * @brief Read the shader file
     * 
     * @param file_name 
     * @return const char* 
     */
    std::string ReadShaderFile(std::string file_name);
};