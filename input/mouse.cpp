#include "mouse.h"
#include "../window/window.h"

#define SENSITIVITY 0.06f

double lastX = WINDOW_STARTING_WIDTH;
double lastY = WINDOW_STARTING_HEIGHT;

double pitch = 0.0;
double yaw = -90.0;

void mouse_callback(__attribute__((unused)) GLFWwindow* window, double xPos, double yPos) {
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
