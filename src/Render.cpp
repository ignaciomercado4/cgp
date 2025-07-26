#include <GL/glew.h>
#include "Render.h"
#include "Shader.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

GLuint Render::_quadVAO = 0;
extern GLuint renderingProgram;
int Render::_tilemap[10][10] = {0};
float Render::TILE_SIZE = 64.0f;

void Render::drawTile(float x, float y, float type)
{
    if (Render::_quadVAO == 0)
    {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices = {2, 1, 0, 0, 3, 2};
        Vertex v0 = {glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec2(0.0f, 1.0f)};
        Vertex v1 = {glm::vec3(0.5f, 0.5f, 0.0f), glm::vec2(1.0f, 1.0f)};
        Vertex v2 = {glm::vec3(0.5f, -0.5f, 0.0f), glm::vec2(1.0f, 0.0f)};
        Vertex v3 = {glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0.0f, 0.0f)};

        vertices.push_back(v0);
        vertices.push_back(v1);
        vertices.push_back(v2);
        vertices.push_back(v3);

        unsigned int VBO, EBO;
        glGenVertexArrays(1, &Render::_quadVAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glBindVertexArray(Render::_quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, uv));

        glBindVertexArray(0);
    }

    glm::mat4 modelMat4(1.0f);
    modelMat4 = glm::translate(modelMat4, glm::vec3(x, y, 0.0f));
    modelMat4 = glm::scale(modelMat4, glm::vec3(TILE_SIZE, TILE_SIZE, 1.0f));

    Shader::setMat4(renderingProgram, "u_Model", modelMat4);

    glBindVertexArray(Render::_quadVAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Render::drawTilemap()
{
    for (int row = 0; row < 10; row++)
    {
        for (int col = 0; col < 10; col++)
        {
            int tileType = _tilemap[row][col];
            if (tileType != 0)
            {
                float x = col * TILE_SIZE;
                float y = row * TILE_SIZE;
                
                drawTile(x, y, tileType);
            }
        }
    }
}

void Render::initTilemap()
{
    // testing tilemap
    // 0 = empty, 1 = solid
    
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            _tilemap[i][j] = 0;
        }
    }
    
    // upper and lower edges
    for (int col = 0; col < 10; col++) {
        _tilemap[0][col] = 1;  
        _tilemap[9][col] = 1;  
    }
    
    // left and right edges
    for (int row = 0; row < 10; row++) {
        _tilemap[row][0] = 1;
        _tilemap[row][9] = 1;
    }
    
    // some in the middle
    _tilemap[3][3] = 1;
    _tilemap[3][4] = 1;
    _tilemap[4][3] = 1;
    _tilemap[4][4] = 1;
    
    _tilemap[6][6] = 1;
    _tilemap[6][7] = 1;
    _tilemap[7][6] = 1;
    _tilemap[7][7] = 1;
    
    std::cout << "Tilemap init succesfully" << std::endl;
}
