#ifndef RENDERER_MOUSE_H
#define RENDERER_MOUSE_H
#include <GLFW/glfw3.h>

void mouse_callback(__attribute__((unused)) GLFWwindow* window, double xPos, double yPos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

double getPitch();
double getYaw();

#endif //RENDERER_MOUSE_H
