#include "keyboard.h"

#include "../window/window.h"

// To send the camera movement info
#include "../camera/camera.h"

unsigned char wireframe = 0;

void key_callback(GLFWwindow* window, int key, __attribute__((unused)) int scancode, int action, __attribute__((unused)) int mods) {
    /************************************************** Begin key press logic **************************************************/
    if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_ESCAPE: {
                glfwSetWindowShouldClose(window, true);
                break;
            }
            case GLFW_KEY_P: {
                if (!wireframe) {
                    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                    wireframe = 1;
                } else {
                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                    wireframe = 0;
                }
                break;
            }
            /* Begin input keys. */
            case GLFW_KEY_W:
                move_forward();
                break;
            case GLFW_KEY_A:
                move_left();
                break;
            case GLFW_KEY_S:
                move_backwards();
                break;
            case GLFW_KEY_D:
                move_right();
                break;
            case GLFW_KEY_UP:
                move_forward();
                break;
            case GLFW_KEY_LEFT:
                move_left();
                break;
            case GLFW_KEY_DOWN:
                move_backwards();
                break;
            case GLFW_KEY_RIGHT:
                move_right();
                break;
            case GLFW_KEY_SPACE:
                move_up();
                break;
            case GLFW_KEY_C:
                move_down();
                break;
            /* End input keys. */
            default:
                break;
        }
    }
    /************************************************** End key press logic **************************************************/

    /************************************************** Begin key release logic **************************************************/
    if (action == GLFW_RELEASE) {
        switch (key) {
            /* Begin input keys. */
            case GLFW_KEY_W:
                stop_move_forwards();
                break;
            case GLFW_KEY_A:
                stop_move_left();
                break;
            case GLFW_KEY_S:
                stop_move_backwards();
                break;
            case GLFW_KEY_D:
                stop_move_right();
                break;
            case GLFW_KEY_UP:
                stop_move_forwards();
                break;
            case GLFW_KEY_LEFT:
                stop_move_left();
                break;
            case GLFW_KEY_DOWN:
                stop_move_backwards();
                break;
            case GLFW_KEY_RIGHT:
                stop_move_right();
                break;
            case GLFW_KEY_SPACE:
                stop_move_up();
                break;
            case GLFW_KEY_C:
                stop_move_down();
                break;
                /* End input keys. */
            default:
                break;
        }
    }
    /************************************************** End key release logic **************************************************/
}
