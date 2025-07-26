#include "Input.h"

bool Input::_keyPressed[GLFW_KEY_LAST + 1] = {false};
bool Input::_keyDown[GLFW_KEY_LAST + 1] = {false};
bool Input::_keyDownLastFrame[GLFW_KEY_LAST + 1] = {false};

void Input::update(GLFWwindow *window)
{
    for (int i = 30; i < 360; i++)
    {
        Input::_keyDown[i] = (glfwGetKey(window, i) == GLFW_PRESS);
        Input::_keyPressed[i] = (Input::_keyDown[i] && !Input::_keyDownLastFrame[i]);
        Input::_keyDownLastFrame[i] = Input::_keyDown[i];
    }
}

bool Input::KeyPressed(unsigned int keycode)
{
    return Input::_keyPressed[keycode];
}

bool Input::KeyDown(unsigned int keycode)
{
    return Input::_keyDown[keycode];
}