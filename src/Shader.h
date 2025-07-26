#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace Shader
{
    GLuint createShaderProgram(std::string vertexShaderPath, std::string fragmentShaderPath);
    void setMat4(GLuint program, std::string name, glm::mat4 value);
};


#endif