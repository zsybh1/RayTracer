#ifndef DIFFUSE_LIGHT_H_
#define DIFFUSE_LIGHT_H_

#include <material.h>
#include <texture.h>

class Diffuse_light : public Material {
public:
    Texture *albedo;

    Diffuse_light(Texture *a) : albedo(a) {}
    bool scatter(const ray &r, const HitResult &rec, vec3 &attenuation, ray &next) const {
        return false;
    }
    vec3 emit(float u, float v) {
        return albedo->value(u, v);
    }
};

#endif