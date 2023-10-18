#include "mouse.h"
#include "../window/window.h"

#include <imgui.h>

#define SENSITIVITY 0.06f

double lastX = WINDOW_STARTING_WIDTH;
double lastY = WINDOW_STARTING_HEIGHT;

double pitch = 0.0;
double yaw = -90.0;

void mouse_callback(__attribute__((unused)) GLFWwindow* window, double xPos, double yPos) {
    if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL) return;
    
    double XOffset = xPos - lastX;
    double YOffset = lastY - yPos; // reversed since y-coordinates range from bottom to top
    lastX = xPos;
    lastY = yPos;

    XOffset *= SENSITIVITY;
    YOffset *= SENSITIVITY;

    yaw   += XOffset;
    pitch += YOffset;

    if(pitch > 89.0f)
        pitch =  89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;
}

double getPitch() {
    return pitch;
}

double getYaw() {
    return yaw;
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    if (state == GLFW_PRESS && !ImGui::GetIO().WantCaptureMouse) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
}
