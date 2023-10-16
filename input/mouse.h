#ifndef RENDERER_MOUSE_H
#define RENDERER_MOUSE_H
#include <GLFW/glfw3.h>

void mouse_callback(__attribute__((unused)) GLFWwindow* window, double xPos, double yPos);

double getPitch();
double getYaw();

#endif //RENDERER_MOUSE_H
