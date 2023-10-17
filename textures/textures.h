#ifndef RENDERER_TEXTURES_H
#define RENDERER_TEXTURES_H

enum TextureType {
    BRICK, GRANITE
};

unsigned int load_texture(TextureType texture);

#endif //RENDERER_TEXTURES_H
