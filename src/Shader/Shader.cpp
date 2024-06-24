#include <Shader.h>
#include <iostream>
#include <fstream>
#include <sstream>

GLuint Shader::CompileShader(std::string file_name, GLenum ShaderType)
{
    // Had to make a copy, otherwise .c_str() will throw out junk since the reference is no longer valid.
    std::string file_content = ReadShaderFile(file_name);
    const char *shader_src = file_content.c_str();

    unsigned int shader = glCreateShader(ShaderType);
    glShaderSource(shader, 1, &shader_src, NULL);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    // For Debugging Purposes
    std::string shader_type_string = (ShaderType == GL_VERTEX_SHADER) ? "GL_VERTEX_SHADER" : (ShaderType == GL_FRAGMENT_SHADER) ? "GL_FRAGMENT_SHADER": "UNKNOWN_TYPE";
    
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::" << shader_type_string << "::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    return shader;
}

void Shader::LinkShader(GLuint shader)
{

    // Check if we have the shader program initialized
    if (!this->has_program)
    {
        this->shader_id = glCreateProgram();
        this->has_program = true;
    }

    GLuint shader_program = this->shader_id;
    glAttachShader(shader_program, shader);
    glLinkProgram(shader_program);

    int success;
    char infoLog[512];
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << infoLog << std::endl;
    }
    glDeleteShader(shader);
}

std::string Shader::ReadShaderFile(std::string file_name)
{
    // TODO: Throw errors when failed to read file
    std::ifstream inputFile(file_name);
    std::stringstream buffer;
    buffer << inputFile.rdbuf();
    return buffer.str();
}

GLuint Shader::GetShaderID()
{
    return this->shader_id;
}

void Shader::DeleteShader()
{
    glDeleteProgram(this->shader_id);

    // We no longer have the shader program.
    this->has_program = false;
}