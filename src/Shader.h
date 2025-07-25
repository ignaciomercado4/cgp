#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <GLFW/glfw3.h>

namespace Shader
{
    GLuint createShaderProgram(std::string vertexShaderPath, std::string fragmentShaderPath);
};


#endif