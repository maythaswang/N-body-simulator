#pragma once
#include <GLCommon.h>
#include <string>

// TODO: Maybe rename this class ....
class Shader
{
public:
    /**
     * @brief Construct a new Shader object
     *
     */
    Shader()
    {
        hasProgram = false;
        shaderID = 0;
    }

    /**
     * @brief Create a Shader according to the shader type specified.
     * For instance, you can create fragment and vertex shader.
     *
     * @param fileName
     * @param SHADER_TYPE
     * @return status of shader creation
     */
    GLuint CompileShader(std::string, GLenum);

    /**
     * @brief Link shader that has been built by CompileShader.
     * @note The shader that has been inputted will be deleted after this function call.
     *
     * @param shader
     */
    void LinkShader(GLuint);

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
    GLuint shaderID;
    bool hasProgram;

    /**
     * @brief Read the shader file
     *
     * @param fileName
     * @return const char*
     */
    std::string ReadShaderFile(std::string);
};