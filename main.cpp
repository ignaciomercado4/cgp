#include <iostream>
#include <cmath>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600
#define numVAOs 1

GLuint renderingProgram;
GLuint vao[numVAOs];

std::string getShaderSource(std::string path)
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

void printShaderLog(GLuint shader)
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

void printProgramLog(int program)
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

bool checkOpenGLError()
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

GLuint createShaderProgram(std::string vertexShaderPath, std::string fragmentShaderPath)
{
    std::string vertexShaderCode = getShaderSource(vertexShaderPath);
    std::string fragmentShaderCode = getShaderSource(fragmentShaderPath);
    const char *vertexShaderSource = vertexShaderCode.c_str();
    const char *fragmentShaderSource = fragmentShaderCode.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    GLuint vfShader = glCreateProgram();
    glAttachShader(vfShader, vertexShader);
    glAttachShader(vfShader, fragmentShader);
    glLinkProgram(vfShader);

    return vfShader;
}

void init(GLFWwindow *window)
{
    renderingProgram = createShaderProgram("./shader.vert", "./shader.frag");
    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);
}

void display(GLFWwindow *window, float currentTime)
{
    glUseProgram(renderingProgram);
    glPointSize(30.0f);
    glDrawArrays(GL_POINTS, 0, 1);
}

int main()
{
    if (!glfwInit())
    {
        std::cerr << "Error inicializando GLFW" << std::endl;
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