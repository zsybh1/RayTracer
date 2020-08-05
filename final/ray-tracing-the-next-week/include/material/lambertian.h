#ifndef LAMBERTIAN_H_
#define LAMBERTIAN_H_

#include <material.h>
#include <random.h>
#include <texture.h>

class Lambertian : public Material {
public:
    Texture *albedo;

    Lambertian(Texture *a) : albedo(a) {}
    bool scatter(const ray &r, const HitResult &rec, vec3 &attenuation, ray &next) const {
        next = ray(rec.p, unit(rec.normal) + random_point_in_unit_sphere(), r.time());
        attenuation = albedo->value(rec.u, rec.v);
        return true;
    }
};

#endif