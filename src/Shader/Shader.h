#pragma once
#include <GLCommon.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>

// TODO: Maybe rename this class ....
class Shader
{
public:
    /**
     * @brief Construct a new Shader object
     *
     */
    Shader();

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

    // Utility Setter for Uniform Variable
    // ----------------------------------------------------------------------------

    void SetBool(const std::string &name, bool value);
    void SetInt(const std::string &name, int value);
    void SetFloat(const std::string &name, float value);
    void SetVec2(const std::string &name, const glm::vec2 &value);
    void SetVec3(const std::string &name, const glm::vec3 &value);
    void SetVec4(const std::string &name, const glm::vec4 &value);
    void SetMat2(const std::string &name, const glm::mat2 &);
    void SetMat3(const std::string &name, const glm::mat3 &);
    void SetMat4(const std::string &name, const glm::mat4 &);

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