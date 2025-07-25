#include <iostream>
#include <cmath>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Utils.h"
#include "Render.h"
#include "Shader.h"
#include <glm/glm.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600
#define numVAOs 1

GLuint vao[numVAOs];
GLuint renderingProgram;
unsigned int cobblestoneTextID;

struct Transform
{
    glm::vec3 position;
};

namespace Game
{
    Transform _camera;
    float _cameraSpeed = 0.5f;

    // ADD KEY CALLBACKS
};

namespace Texture
{
    unsigned int loadTexture(std::string path)
    {
        unsigned int textureID;
        glGenTextures(1, &textureID);

        int nrChannels, width, height;
        unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            GLenum format;
            if (nrChannels == 1)
                format = GL_RED;
            else if (nrChannels == 3)
                format = GL_RGB;
            else if (nrChannels == 4)
                format = GL_RGBA;

            glBindTexture(GL_TEXTURE_2D, textureID);
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            stbi_image_free(data);
        }
        else
        {
            std::cout << "Texture failed to load at path: " << path << std::endl;
            stbi_image_free(data);
        }

        return textureID;
    }
}



void init(GLFWwindow *window)
{
    renderingProgram = Shader::createShaderProgram("shaders/vertShader.glsl", "shaders/fragShader.glsl");
    cobblestoneTextID = Texture::loadTexture("textures/cobblestone.png");
    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);
}

void display(GLFWwindow *window, float currentTime)
{
    glUseProgram(renderingProgram);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, cobblestoneTextID);

    glUniform1i(glGetUniformLocation(renderingProgram, "uTexture"), 0);
    Render::drawTile();
}

int main()
{
    if (!glfwInit())
    {
        std::cerr << "Error in GLFW init" << std::endl;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Window :D", NULL, NULL);
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        std::cerr << EXIT_FAILURE << std::endl;
    }

    glfwSwapInterval(1);
    init(window);

    while (!glfwWindowShouldClose(window))
    {
        display(window, glfwGetTime());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}