#ifndef RENDER_H
#define RENDER_H

#include <glm/glm.hpp>
#include <GL/glew.h>

struct Vertex
{
    glm::vec2 position;
    glm::vec2 uv;
};

namespace Render
{
    extern GLuint _quadVAO;          
    extern int _tilemap[10][10];     

    void drawTile();                  
}

#endif
