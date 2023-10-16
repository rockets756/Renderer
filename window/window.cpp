#include "window.h"
#include <iostream>
#include "../input/keyboard.h"
#include "../input/mouse.h"

int window_width = WINDOW_STARTING_WIDTH;
int window_height = WINDOW_STARTING_HEIGHT;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

GLFWwindow* createWindow() {
    GLFWwindow* window = glfwCreateWindow(WINDOW_STARTING_WIDTH, WINDOW_STARTING_HEIGHT, WINDOW_STARTING_TITLE, NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return NULL;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    glViewport(0, 0, WINDOW_STARTING_WIDTH, WINDOW_STARTING_HEIGHT);
    return window;
}

int getWindowWidth() {
    return window_width;
}

int getWindowHeight() {
    return window_height;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    window_width = width;
    window_height = height;
    glViewport(0, 0, width, height);
}
