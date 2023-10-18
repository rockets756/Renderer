#ifndef RENDERER_LOADER_H
#define RENDERER_LOADER_H
#include <vector>
#include <../rendering/vao/vao.h>
#include <../rendering/vbo/vbo.h>

struct model {
    // std::vector<float> gpuData;
    int gpu_data_length;
    VAO vao;
    VBO vbo;
};

struct model load_model(const char *file_name);
void draw_model(model model_to_draw);
void destroy_model(model model_to_destroy);

#endif //RENDERER_LOADER_H
