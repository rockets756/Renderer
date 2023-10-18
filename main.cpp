// imgui must be included before glfw and glad
#include <imgui.h>
#include <imgui_impl_glfw.h>
//#include <imgui_impl_opengl3.h>
// glad must be included before glfw
#include <glad.h>
#include <GLFW/glfw3.h>
// iostream is included for debugging
#include <iostream>

#include "debug/debug.h"
#include "window/window.h"
#include "rendering/shaders/shaders.h"
#include "camera/camera.h"
#include "rendering/vao/vao.h"
#include "rendering/vbo/vbo.h"
#include "rendering/textures/textures.h"

#include "loader/loader.h"

#define FPS (1 / deltaTime)
#define NUMBER_OF_VERTICES (sizeof(vertices) / sizeof(float) / 6)

GLFWwindow* window;

double timeI;
double timeF;
double deltaTime;

float vertices[] = {
        // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f    // top left
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

    struct VAO vao = vao_create();
    struct VBO vbo = vbo_create(GL_ARRAY_BUFFER, true);
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    vao_bind(vao);
    vbo_buffer(vbo, vertices, 0, sizeof(vertices));

    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Set vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Set background color
    glClearColor(WINDOW_STARTING_COLOR);

    load_texture(BRICK);

    // Imgui implementation
    init_imgui(window);

    model testModel = load_model("vertices");

    // Main loop
    while(!glfwWindowShouldClose(window)) {
        timeI = glfwGetTime();
        // printf("FPS: %f\n", FPS);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        update_imgui();

        // Calculate camera
        update_camera(shader_program, (float) deltaTime);

        // Draw here
        glUseProgram(shader_program);
        vao_bind(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        draw_model(testModel);
        render_imgui();

        // Swap buffers (display what we have rendered to the screen)
        glfwSwapBuffers(window);
        glfwPollEvents();
        timeF = glfwGetTime();
        deltaTime = timeF - timeI;
    }

    // Free resources and close
    shutdown_imgui();
    destroy_model(testModel);
    vao_destroy(vao);
    vbo_destroy(vbo);
    glDeleteBuffers(1, &EBO);
    glUseProgram(0);
    glDeleteProgram(shader_program);
    glfwTerminate();
    return 0;
}
