#include "textures.h"

#include <stdio.h>
#include <glad.h>
#include "image.h"

unsigned int load_texture(TextureType texture) {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    switch (texture) {
        case BRICK: {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (int) brick_image.width, (int) brick_image.height, 0, GL_RGB, GL_UNSIGNED_BYTE, brick_image.pixel_data);
            break;
        }
        case GRANITE: {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (int) granite_image.width, (int) granite_image.height, 0, GL_RGB, GL_UNSIGNED_BYTE, granite_image.pixel_data);
            break;
        }
    }
    glGenerateMipmap(GL_TEXTURE_2D);
    return textureID;
}
