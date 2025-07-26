#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Utils.h"

GLuint Shader::createShaderProgram(std::string vertexShaderPath, std::string fragmentShaderPath)
{
    std::string vertexShaderCode = Utils::getShaderSource(vertexShaderPath);
    std::string fragmentShaderCode = Utils::getShaderSource(fragmentShaderPath);
    const char *vertexShaderSource = vertexShaderCode.c_str();
    const char *fragmentShaderSource = fragmentShaderCode.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    GLint success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "Error compiling Vertex Shader:\n"
                  << infoLog << std::endl;
    }

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "Error compiling Fragment Shader:\n"
                  << infoLog << std::endl;
    }

    GLuint vfShader = glCreateProgram();
    glAttachShader(vfShader, vertexShader);
    glAttachShader(vfShader, fragmentShader);
    glLinkProgram(vfShader);

    glGetProgramiv(vfShader, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(vfShader, 512, NULL, infoLog);
        std::cerr << "Error linking shader program:\n"
                  << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return vfShader;
}


void Shader::setMat4(GLuint program, const std::string name, glm::mat4 value)
{
    glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &value[0][0]);
}
