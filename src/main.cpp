#include <iostream>
#include <cmath>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Utils.h"
#include "Render.h"
#include "Shader.h"
#include "Player.h"
#include "Texture.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

GLuint renderingProgram;
unsigned int cobblestoneTextID;
glm::mat4 currentView;
glm::mat4 currentProjection;
Player::Player player = {glm::vec2(0.0f, 0.0f)};

void init(GLFWwindow *window)
{
    std::cout << "||| init |||" << std::endl;

    renderingProgram = Shader::createShaderProgram("shaders/vertShader.glsl", "shaders/fragShader.glsl");
    std::cout << "Shader program created: " << renderingProgram << std::endl;
    
    cobblestoneTextID = Texture::loadTexture("textures/cobblestone.png");
    std::cout << "Texture loaded: " << cobblestoneTextID << std::endl;

    Render::initTilemap();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    std::cout << "||| finished init |||" << std::endl;
}

void display(GLFWwindow *window, float currentTime)
{
    glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);        
    
    glUseProgram(renderingProgram);      
    
    glm::vec2 camPos = player.position;
    currentView = glm::translate(glm::mat4(1.0f), glm::vec3(-camPos.x, -camPos.y, 0.0f));

    currentProjection = glm::ortho(
        0.0f, static_cast<float>(WINDOW_WIDTH),
        0.0f, static_cast<float>(WINDOW_HEIGHT),
        -1.0f, 1.0f);

    Shader::setMat4(renderingProgram, "u_View", currentView);
    Shader::setMat4(renderingProgram, "u_Projection", currentProjection);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, cobblestoneTextID);
    glUniform1i(glGetUniformLocation(renderingProgram, "uTexture"), 0);

    Render::drawTilemap();
    
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cout << "OpenGL Error: " << error << std::endl;
    }
}

int main()
{
    if (!glfwInit())
    {
        std::cerr << "Error in GLFW init" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 
    
    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Window :D", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    glfwSwapInterval(1);
    init(window);

    while (!glfwWindowShouldClose(window))
    {
        Input::update(window);
        Player::keyboardUpdate(player);
        display(window, glfwGetTime());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}