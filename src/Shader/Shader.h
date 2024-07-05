#pragma once
#include <GLCommon.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

/**
 * @brief Store, Initialize, Link, Compile, Destroy Shaders.
 * 
 */
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
    GLuint compile_shader(std::string, GLenum);

    /**
     * @brief Link shader that has been built by CompileShader.
     * @note The shader that has been inputted will be deleted after this function call.
     *
     * @param shader
     */
    void link_shader(GLuint);

    /**
     * @brief Get the ShaderID
     *
     * @return GLuint
     */
    GLuint get_shader_id();

    /**
     * @brief Delete the shader program
     *
     */
    void delete_shader();

    /**
     * @brief Use the shader program.
     * 
     */
    void use();

    // Utility Setter for Uniform Variable
    // ----------------------------------------------------------------------------

    void set_bool(const std::string &name, bool value);
    void set_int(const std::string &name, int value);
    void set_float(const std::string &name, float value);
    void set_vec2(const std::string &name, const glm::vec2 &value);
    void set_vec3(const std::string &name, const glm::vec3 &value);
    void set_vec4(const std::string &name, const glm::vec4 &value);
    void set_mat2(const std::string &name, const glm::mat2 &);
    void set_mat3(const std::string &name, const glm::mat3 &);
    void set_mat4(const std::string &name, const glm::mat4 &);

private:
    GLuint shader_id;
    bool has_program;

    /**
     * @brief Read the shader file
     *
     * @param fileName
     * @return const char*
     */
    std::string read_shader_file(std::string);
};