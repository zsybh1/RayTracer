#ifndef MOVING_SPHERE_H_
#define MOVING_SPHERE_H_

#include <hitable.h>
#include <ray.h>

class Moving_sphere : public Hitable {
public:
    vec3 center0, center1;
    float time0, time1;
    float radius;
    Material *material;

    Moving_sphere() {}
    Moving_sphere(float t0, const vec3 &c0, float t1, const vec3 &c1, float r,
                  Material *mat)
        : time0(t0), center0(c0), time1(t1), center1(c1), radius(r),
          material(mat) {}
    bool hit(const ray &r, float tmin, float tmax, HitResult &hitResult) const;
    bool bounding_box(float t0, float t1, AABB &box) const;

    vec3 center(float t) const {
        return center0 + ((t - time0) / (time1 - time0)) * (center1 - center0);
    }
};

bool Moving_sphere::hit(const ray &r, float tmin, float tmax,
                        HitResult &hitResult) const {
    vec3 OC = r.origin() - center(r.time());
    float A = dot(r.direction(), r.direction());
    float B = 2.0f * dot(r.direction(), OC);
    float C = dot(OC, OC) - radius * radius;
    float delta = B * B - 4 * A * C;
    if (delta > 0) {
        float t = (-B - std::sqrt(delta)) / (2 * A);
        if (tmin < t && t < tmax) {
            hitResult.t = t;
        } else {
            t = (-B + std::sqrt(delta)) / (2 * A);
            if (tmin < t && t < tmax) {
                hitResult.t = t;
            } else {
                return false;
            }
        }
        hitResult.p = r(t);
        hitResult.normal = (hitResult.p - center(r.time())) / radius;
        hitResult.mateial = material;
        return true;
    }
    return false;
}

bool Moving_sphere::bounding_box(float t0, float t1, AABB &box) const {
    AABB box0 = AABB(center(t0) - vec3(radius), center(t0) + vec3(radius));
    AABB box1 = AABB(center(t1) - vec3(radius), center(t1) + vec3(radius));
    box = surrounding_box(box0, box1);
    return true;
}

#endif