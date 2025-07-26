#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>

namespace Input
{
    extern bool _keyPressed[GLFW_KEY_LAST + 1];
    extern bool _keyDown[GLFW_KEY_LAST + 1];
    extern bool _keyDownLastFrame[GLFW_KEY_LAST + 1];

    void update(GLFWwindow* window);

    bool KeyPressed(unsigned int keycode);

	bool KeyDown(unsigned int keycode);
}

#endif