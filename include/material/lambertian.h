#ifndef LAMBERTIAN_H_
#define LAMBERTIAN_H_

#include <material.h>
#include <random.h>

class Lambertian : public Material {
public:
    vec3 albedo;

    Lambertian(const vec3 &a) : albedo(a) {}
    bool scatter(const ray &r, const HitResult &rec, vec3 &attenuation, ray &next) const {
        next = ray(rec.p, unit(rec.normal) + random_point_in_unit_sphere());
        attenuation = albedo;
        return true;
    }
};

#endif