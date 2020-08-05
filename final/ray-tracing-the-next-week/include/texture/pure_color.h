#ifndef PURE_COLOR_H_
#define PURE_COLOR_H_

#include <texture.h>

class Pure_color : public Texture {
public:
    vec3 color;

    Pure_color(const vec3 &c) : color(c) {}

    vec3 value(float u, float v) const {
        return color;
    }
};

#endif