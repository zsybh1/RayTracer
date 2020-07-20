#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <hitable.h>

class Material {
public:
    virtual bool scatter(const ray &r, const HitResult &rec, vec3 &attenuation, ray &next) const = 0;
};

#endif