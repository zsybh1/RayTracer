#ifndef HITABLE_H_
#define HITABLE_H_

#include <ray.h>
#include <AABB.h>

class Material;

struct HitResult {
    float t;
    vec3 p;
    vec3 normal;
    Material *mateial;
    float u, v;
};

class Hitable{
public:
    virtual bool hit(const ray &r, float tmin, float tmax, HitResult &hitResult) const = 0;
    virtual bool bounding_box(float t0, float t1, AABB &box) const = 0;
};

#endif