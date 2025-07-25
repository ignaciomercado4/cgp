#include "Utils.h"
#include <fstream>

std::string Utils::getShaderSource(std::string path)
{
    std::ifstream file(path);
    std::string str;
    std::string code;

    while (std::getline(file, str))
    {

        code += str;
        code.push_back('\n');
    }

    return code;
}

void Utils::printShaderLog(GLuint shader)
{
    int length = 0;
    int chWritten = 0;
    char *log;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
    if (length > 0)
    {
        log = (char*)malloc(length);
        glGetShaderInfoLog(shader, length, &chWritten, log);
        std::cout << "Shader info log: " << log << std::endl;
        free(log);
    }
}

void Utils::printProgramLog(int program)
{
    int length = 0;
    int chWritten = 0;
    char *log;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
    if (length > 0)
    {
        log = (char*)malloc(length);
        glGetProgramInfoLog(program, length, &chWritten, log);
        std::cout << "Program info log: " << log << std::endl;
        free(log);
    }
}

bool Utils::checkOpenGLError()
{
    bool foundError = false;
    int glError = glGetError();
    while (glError != GL_NO_ERROR)
    {
        std::cout << "glError: " << glError << std::endl;
        foundError = true;
        glError = glGetError();
    }

    return foundError;
}