#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 color;
out vec2 texCoord;

uniform mat4 view;
uniform mat4 proj;

void main() {
    gl_Position = proj * view * vec4(aPos, 1.0);
    color = aColor;
    texCoord = aTexCoord;
}
