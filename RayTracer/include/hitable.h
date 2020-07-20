#ifndef HITABLE_H_
#define HITABLE_H_

#include <ray.h>

class Material;

struct HitResult {
    float t;
    vec3 p;
    vec3 normal;
    Material *mateial;
};

class Hitable{
public:
    virtual bool hit(const ray &r, float tmin, float tmax, HitResult &hitResult) const = 0;
};

#endif