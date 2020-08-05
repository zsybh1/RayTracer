#ifndef METAL_H_
#define METAL_H_

#include <material.h>
#include <random.h>
#include <texture.h>

class Metal : public Material{
public:
    Texture *albedo;
    float roughness;

    Metal(Texture *a, float r) : albedo(a), roughness(r) {}
    bool scatter(const ray &r, const HitResult &rec, vec3 &attenuation, ray &next) const {
        vec3 reflect_direction = reflect(r.direction(), rec.normal);
        next = ray(rec.p, reflect_direction + roughness * random_point_in_unit_sphere(), r.time());
        attenuation = albedo->value(rec.u, rec.v);
        return true;
    }
};

#endif