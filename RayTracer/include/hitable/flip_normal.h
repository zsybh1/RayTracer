#ifndef FLIP_NORMAL_H_
#define FLIP_NORMAL_H_

#include <hitable.h>

class Filp_normal : public Hitable {
public:
    Hitable *hitable;

    Filp_normal(Hitable *hit) : hitable(hit) {}
    bool hit(const ray &r, float tmin, float tmax, HitResult &hitResult) const{
        if (hitable->hit(r, tmin, tmax, hitResult)) {
            hitResult.normal = -hitResult.normal;
            return true;
        }
        return false;
    }
    bool bounding_box(float t0, float t1, AABB &box) const {
        return hitable->bounding_box(t0, t1, box);
    };
};

#endif