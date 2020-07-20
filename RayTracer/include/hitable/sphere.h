#ifndef SPHERE_H_
#define SPHERE_H_

#include <hitable.h>

class Sphere : public Hitable{
public:
    vec3 center;
    float radius;
    Material *material;

    Sphere() {}
    Sphere(const vec3 &c, float r, Material *mat) : center(c), radius(r), material(mat) {}
    bool hit(const ray &r, float tmin, float tmax, HitResult &hitResult) const;
};

bool Sphere::hit(const ray &r, float tmin, float tmax, HitResult &hitResult) const {
    vec3 OC = r.origin() - center;
    float A = dot(r.direction(), r.direction());
    float B = 2.0f * dot(r.direction(), OC);
    float C = dot(OC, OC) - radius * radius;
    float delta = B * B - 4 * A * C;
    if (delta > 0) {
        float t = (-B - std::sqrt(delta)) / (2 * A);
        if (tmin < t && t < tmax) {
            hitResult.t = t;
        }
        else {
            t = (-B + std::sqrt(delta)) / (2 * A);
            if (tmin < t && t < tmax) {
                hitResult.t = t;
            }
            else {
                return false;
            }
        }
        hitResult.p = r(t);
        hitResult.normal = (hitResult.p - center) / radius;
        hitResult.mateial = material;
        return true;
    }
    return false;
}

#endif