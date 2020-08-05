#ifndef ISOTROPIC_H_
#define ISOTROPIC_H_

#include <material.h>
#include <texture.h>
#include <random.h>

class isotropic : public Material {
public:
    Texture *albedo;

    isotropic(Texture *a) : albedo(a) {}
    bool scatter(const ray &r, const HitResult &rec, vec3 &attenuation, ray &next) const {
        next = ray(rec.p, random_point_in_unit_sphere(), r.time());
        attenuation = albedo->value(rec.u, rec.v);
        return true;
    }
};

#endif