#include <glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "window/window.h"
#include "shaders/shaders.h"
#include "camera/camera.h"

#define FPS (1 / deltaTime)
#define NUMBER_OF_VERTICES (sizeof(vertices) / sizeof(float) / 6)

GLFWwindow* window;

double timeI;
double timeF;
double deltaTime;

float vertices[] = {
        // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f, // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f  // top left
};
unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
};

int main() {
    // Init glfw (GLFW/glfw3.h)
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window (window/window.h)
    window = createWindow();
    if (window == nullptr) return 1;

    // Init glad (glad.h)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Makes sure things are being ordered correctly
    glEnable(GL_DEPTH_TEST);

    // Compile Shaders (shaders/shaders.h)
    unsigned int shader_program = compile_shaders();
    if (!shader_program) return 1;
    glUseProgram(shader_program);

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Set vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glBindVertexArray(0);

    // Set background color
    glClearColor(WINDOW_STARTING_COLOR);

    // Main loop
    while(!glfwWindowShouldClose(window)) {
        timeI = glfwGetTime();
        printf("FPS: %f\n", FPS);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Calculate camera
        update_camera(shader_program, (float) deltaTime);

        // Draw here
        glUseProgram(shader_program);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        // Swap buffers (display what we have rendered to the screen)
        glfwSwapBuffers(window);
        glfwPollEvents();
        timeF = glfwGetTime();
        deltaTime = timeF - timeI;
    }

    // Free resources and close
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glUseProgram(0);
    glDeleteProgram(shader_program);
    glfwTerminate();
    return 0;
}
