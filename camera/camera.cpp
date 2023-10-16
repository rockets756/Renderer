#include "camera.h"
#include <glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../window/window.h"
#include "../input/mouse.h"

#define CAMERA_SPEED (5.0f * deltaTime)

using namespace glm;

vec3 cameraMovement = vec3(0); // Set by keyboard input

// Camera positioning stuff. Also makes LookAt function work properly
vec3 cameraPos = vec3(0.0f, 0.0f, 3.0f);
vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f);
vec3 cameraTarget = vec3(0.0f, 0.0f, 0.0f);

// Camera rotation stuff
vec3 direction;

const vec3 up = vec3(0.0f, 1.0f, 0.0f);

mat4 view = mat4(1);
mat4 proj = mat4(1);

void update_camera(unsigned int shaderProgram, float deltaTime) {
    vec3 cameraDirection = normalize(cameraPos - cameraTarget);
    vec3 cameraRight = normalize(cross(up, cameraDirection));
    vec3 cameraUp = cross(cameraDirection, cameraRight);

    // Update camera position FIXME: Create better algorithm that doesn't use if statements
    if (cameraMovement.x == 1) cameraPos += normalize(cross(cameraFront, cameraUp)) * CAMERA_SPEED;
    else if (cameraMovement.x == -1) cameraPos -= normalize(cross(cameraFront, cameraUp)) * CAMERA_SPEED;
    if (cameraMovement.z == 1) cameraPos += CAMERA_SPEED * cameraFront;
    else if (cameraMovement.z == -1) cameraPos -= CAMERA_SPEED * cameraFront;
    if (cameraMovement.y == 1) cameraPos.y += CAMERA_SPEED;
    else if (cameraMovement.y == -1) cameraPos.y -= CAMERA_SPEED;

    // Update camera direction
    direction.x = cos(radians(getYaw())) * cos(radians(getPitch()));
    direction.y = sin(radians(getPitch()));
    direction.z = sin(radians(getYaw())) * cos(radians(getPitch()));
    cameraFront = normalize(direction);

    proj = perspective(radians(45.0f), (float) getWindowWidth() / (float) getWindowHeight(), 0.1f, 100.0f);
    view = lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    /* Probably not the best place to do this but here we are sending the numbers to the vertex shader for the final calculations. */
    /* May need to change the location number depending on weather or not we are starting at 0 or 1. */
    int viewLoc = glGetUniformLocation(shaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));
    int projLoc = glGetUniformLocation(shaderProgram, "proj");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, value_ptr(proj));
}

/* Movement code
 * cameraPos += CAMERA_SPEED * cameraFront; // up movement
 * cameraPos -= normalize(cross(cameraFront, cameraUp)) * CAMERA_SPEED; // left movement
 * cameraPos -= CAMERA_SPEED * cameraFront; // down movement
 * cameraPos += normalize(cross(cameraFront, cameraUp)) * CAMERA_SPEED; // right movement
 * */

void move_forward() {
    cameraMovement.z += 1;
}
void move_left() {
    cameraMovement.x += -1;
}
void move_backwards() {
    cameraMovement.z += -1;
}
void move_right() {
    cameraMovement.x += 1;
}
void move_up() {
    cameraMovement.y += 1;
}
void move_down() {
    cameraMovement.y += -1;
}

void stop_move_forwards() {
    cameraMovement.z = 0;
}
void stop_move_left() {
    cameraMovement.x = 0;
}
void stop_move_backwards() {
    cameraMovement.z = 0;
}
void stop_move_right() {
    cameraMovement.x = 0;
}
void stop_move_up() {
    cameraMovement.y = 0;
}
void stop_move_down() {
    cameraMovement.y = 0;
}
