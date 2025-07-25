#include <GL/glew.h>
#include <Render.h>
#include <vector>
#include <glm/glm.hpp>

GLuint Render::_quadVAO = 0;
int Render::_tilemap[10][10] = {0};

void Render::drawTile()
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
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, uv));

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    glBindVertexArray(Render::_quadVAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}