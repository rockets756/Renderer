#ifndef RENDERER_WINDOW_H
#define RENDERER_WINDOW_H
#include <GLFW/glfw3.h>

#define WINDOW_STARTING_WIDTH  800
#define WINDOW_STARTING_HEIGHT 800
#define WINDOW_STARTING_TITLE  "Renderer"
#define WINDOW_STARTING_COLOR  0.2f, 0.3f, 0.3f, 1.0f

GLFWwindow* createWindow();
int getWindowWidth();
int getWindowHeight();

#endif //RENDERER_WINDOW_H
