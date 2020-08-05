#ifndef AABB_H_
#define AABB_H_

#include <ray.h>

class AABB {
public:
    vec3 min;
    vec3 max;

    AABB() {}
    AABB(const vec3 &a, const vec3 &b): min(a), max(b) {}
    bool hit(const ray &r, float tmin, float tmax) const{
        for (int i = 0; i < 3; ++i) {
            float t0 = (min[i] - r.origin()[i]) / r.direction()[i];
            float t1 = (max[i] - r.origin()[i]) / r.direction()[i];
            if (t0 > t1) {
                std::swap(t0, t1);
            }
            tmin = t0 > tmin? t0: tmin;
            tmax = t1 < tmax? t1: tmax;
            if (tmin > tmax) {
                return false;
            }
        }
        return true;
    }
};

AABB surrounding_box(const AABB &box0, const AABB &box1) {
    vec3 min(fminf(box0.min.x(), box1.min.x()),fminf(box0.min.y(), box1.min.y()),fminf(box0.min.z(), box1.min.z()));
    vec3 max(fmaxf(box0.max.x(), box1.max.x()),fmaxf(box0.max.y(), box1.max.y()),fmaxf(box0.max.z(), box1.max.z()));
    return AABB(min, max);
}

#endif