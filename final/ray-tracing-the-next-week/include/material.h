#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <hitable.h>

class Material {
public:
    virtual bool scatter(const ray &r, const HitResult &rec, vec3 &attenuation, ray &next) const = 0;
    virtual vec3 emit(float u, float v) {
        return vec3(0.0f);
    }
};

#endif