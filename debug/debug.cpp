#include "debug.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "../rendering/textures/textures.h"

using namespace ImGui;

void init_imgui(GLFWwindow *window) {
    IMGUI_CHECKVERSION();
    CreateContext();
    ImGuiIO& io = GetIO(); (void) io;
    StyleColorsClassic();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void update_imgui() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    NewFrame();
}

void render_imgui() {
    // TextureType window
    Begin("Textures");
    if (Button("Brick")) load_texture(BRICK);
    if (Button("Granite")) load_texture(GRANITE);
    End();

    Render();
    ImGui_ImplOpenGL3_RenderDrawData(GetDrawData());
}

void shutdown_imgui() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    DestroyContext();
}
