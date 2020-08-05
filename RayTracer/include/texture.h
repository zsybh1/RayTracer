#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <vec3.h>

class Texture {
public:
    virtual vec3 value(float u, float v) const = 0;
};

#endif