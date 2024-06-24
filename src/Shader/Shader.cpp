#include <Shader.h>
#include <iostream>
#include <fstream>
#include <sstream>

GLuint Shader::CompileShader(std::string file_name, GLenum ShaderType)
{
    const char *file_content = ReadShaderFile(file_name);

    GLuint shader = glCreateShader(ShaderType);
    glShaderSource(shader, 1, &file_content, NULL);
    glCompileShader(ShaderType);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
        
    }

    return shader; 
}

const char *Shader::ReadShaderFile(std::string file_name)
{

    // TODO: Make a try catch when fails to read file.
    std::ifstream inputFile(file_name);
    std::stringstream buffer;
    buffer << inputFile.rdbuf();
    return buffer.str().c_str();
}