#ifndef RENDERER_KEYBOARD_H
#define RENDERER_KEYBOARD_H
#include <GLFW/glfw3.h>

void key_callback(GLFWwindow* window, int key, __attribute__((unused)) int scancode, int action,
                  __attribute__((unused)) int mods);

#endif //RENDERER_KEYBOARD_H
