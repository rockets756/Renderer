#ifndef RENDERER_VAO_H
#define RENDERER_VAO_H
#include <glad.h>
#include "../vbo/vbo.h"

struct VAO {
    unsigned int handle;
};

struct VAO vao_create();
void vao_destroy(struct VAO self);
void vao_bind(struct VAO self);
void vao_attr(struct VAO self, struct VBO vbo, GLuint index, GLint size, GLenum type, GLsizei stride, size_t offset);

#endif //RENDERER_VAO_H
