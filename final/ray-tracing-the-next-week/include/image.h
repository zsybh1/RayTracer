#ifndef IMAGE_H_
#define IMAGE_H_

#include <vec3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

class Image {
public:
    int width;
    int height;
    int channels;
    unsigned char *data;

    Image() {}
    void operator=(Image &&image){
        width = image.width;
        height = image.height;
        channels = image.channels;
        data = image.data;
        image.data = nullptr;
    }

    Image(const char *path) {
        data = stbi_load(path, &width, &height, &channels, 0);
    }
    Image(int w, int h, int n) : width(w), height(h), channels(n) {
        data = new unsigned char[w*h*n]{0};
    }

    vec3 getRGB(int x, int y) const {
        int pos = (width * y + x) * channels;
        return vec3(data[pos], data[pos+1], data[pos+2]) / 255.99;
    }
    vec3 getRGBA(int x, int y, float &alpha) const {
        int pos = (width * y + x) * channels;
        alpha = data[pos+3] / 255.99;
        return vec3(data[pos], data[pos+1], data[pos+2]) / 255.99;
    }
    vec3 getRGB(float u, float v) const {
        int x = std::min(std::max(int(u * (width - 1)), 0), width - 1);
        int y = std::min(std::max(int((1.0f - v) * (height - 1)), 0), height - 1);
        return getRGB(x, y);
    }
    vec3 getRGBA(float u, float v, float &alpha) const{
        int x = std::min(std::max(int(u * (width - 1)), 0), width - 1);
        int y = std::min(std::max(int((1.0f - v) * (height - 1)), 0), height - 1);
        return getRGBA(x, y, alpha);
    }

    void putRGB(int x, int y, vec3 color) {
        int pos = (width * y + x) * channels;
        color *= 255.99f;
        data[pos] = std::min(std::max((int)color.r(), 0), 255);
        data[pos+1] = std::min(std::max((int)color.g(), 0), 255);
        data[pos+2] = std::min(std::max((int)color.b(), 0), 255);
    }
    void putRGBA(int x, int y, vec3 color, float alpha) {
        int pos = (width * y + x) * channels;
        color *= 255.99f;
        data[pos] = color.r();
        data[pos+1] = color.g();
        data[pos+2] = color.b();
        data[pos+3] = alpha * 255.99f;
    }
    void putRGB(float u, float v, vec3 color) {
        int x = u * (width - 1);
        int y = 1.0f - v * (height - 1);
        putRGB(x, y, color);
    }
    void putRGBA(float u, float v, vec3 color, float alpha) {
        int x = u * (width - 1);
        int y = 1.0f - v * (height - 1);    
        putRGBA(x, y, color, alpha);    
    }

    void save(const char *path) {
        if(channels == 3) {
            stbi_write_bmp(path, width, height, channels, data);
        }
        else if (channels = 4) {
            stbi_write_png(path, width, height, channels, data, width * channels);
        }
    }

    ~Image() {
        delete [] data;
    }
};

#endif