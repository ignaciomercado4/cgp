#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>

namespace Player
{
    struct Player
    {
        glm::vec2 position;
    };

    void keyboardUpdate(Player& player);
}

#endif