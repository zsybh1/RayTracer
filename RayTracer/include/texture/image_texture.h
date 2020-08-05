#ifndef IMAGE_TEXTURE_H_
#define IMAGE_TEXTURE_H_

#include <texture.h>
#include <image.h>

class Image_texture : public Texture {
public:
    Image image;

    Image_texture(const char* path) : image(path) {}
    vec3 value(float u, float v) const {
        return image.getRGB(u, v);
    }
};

#endif