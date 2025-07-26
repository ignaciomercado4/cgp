#include "Player.h"
#include "Input.h"
#include <iostream>

void Player::keyboardUpdate(Player& player)
{
    float camSpeed = 5.0f;
    // std::cout << "Player pos: " << player.position.x << ", " << player.position.y << std::endl;


    if (Input::KeyDown(GLFW_KEY_W)) 
        player.position.y += camSpeed;

    if (Input::KeyDown(GLFW_KEY_S))
        player.position.y -= camSpeed;

    if (Input::KeyDown(GLFW_KEY_A))
        player.position.x -= camSpeed;

    if (Input::KeyDown(GLFW_KEY_D))
        player.position.x += camSpeed;
}
