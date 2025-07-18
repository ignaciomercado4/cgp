#include <iostream>
#include <cmath>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 900
#define numVAOs 1

void init(GLFWwindow* window) {}

void display(GLFWwindow* window, float currentTime) {
    float red = sin(currentTime) * 1.0f;
    glClearColor(red, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

GLuint createShaderProgram() {
    const char *vertexShaderSource = "#version 430 \n"
    "void main(void) \n"
    "{gl_Position = vec4(0.0f, 0.0f, 0.0f, 1.0f);};";

    const char *fragmentShaderSource = "#version 430 \n"
    "out vec4 color; \n"
    "void main(void) \n"
    "{color = vec4(0.0f, 0.0f, 1.0f, 1.0f);};";
    
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Error inicializando GLFW" << std::endl;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Window :D", NULL, NULL);
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cerr << EXIT_FAILURE << std::endl;
    }

    glfwSwapInterval(1);
    init(window);

    while (!glfwWindowShouldClose(window)) {
        display(window, glfwGetTime());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    std::cout << readShaderFile("file.vert");
    
    return 0;
}