
#include <GL/glew.h>
#include <iostream>

namespace Utils
{
    std::string getShaderSource(std::string path);
    void printShaderLog(GLuint shader);
    void printProgramLog(int program);
    bool checkOpenGLError();
}