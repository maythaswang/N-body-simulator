#include <Shader.h>
#include <iostream>
#include <fstream>
#include <sstream>

GLuint Shader::CompileShader(std::string fileName, GLenum SHADER_TYPE)
{
    // Had to make a copy, otherwise .c_str() will throw out junk since the reference is no longer valid.
    std::string file_content = ReadShaderFile(fileName);
    const char *shader_src = file_content.c_str();

    unsigned int shader = glCreateShader(SHADER_TYPE);
    glShaderSource(shader, 1, &shader_src, NULL);
    glCompileShader(shader);

    int success;
    char info_log[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    // For Debugging Purposes
    std::string shader_type_string = (SHADER_TYPE == GL_VERTEX_SHADER) ? "GL_VERTEX_SHADER" : (SHADER_TYPE == GL_FRAGMENT_SHADER) ? "GL_FRAGMENT_SHADER"
                                                                                                                                  : "UNKNOWN_TYPE";

    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, info_log);
        std::cout << "ERROR::SHADER::" << shader_type_string << "::COMPILATION_FAILED\n"
                  << info_log << std::endl;
    }

    return shader;
}

void Shader::LinkShader(GLuint shader)
{

    // Check if we have the shader program initialized
    if (!this->hasProgram)
    {
        this->shaderID = glCreateProgram();
        this->hasProgram = true;
    }

    GLuint shader_program = this->shaderID;
    glAttachShader(shader_program, shader);
    glLinkProgram(shader_program);

    int success;
    char info_log[512];
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shader_program, 512, NULL, info_log);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << info_log << std::endl;
    }
    glDeleteShader(shader);
}

std::string Shader::ReadShaderFile(std::string fileName)
{
    // TODO: Throw errors when failed to read file
    std::ifstream input_file(fileName);
    std::stringstream buffer;
    buffer << input_file.rdbuf();
    return buffer.str();
}

GLuint Shader::GetShaderID()
{
    return this->shaderID;
}

void Shader::DeleteShader()
{
    glDeleteProgram(this->shaderID);

    // We no longer have the shader program.
    this->hasProgram = false;
}