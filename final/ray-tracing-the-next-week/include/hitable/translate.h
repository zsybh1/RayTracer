#ifndef TRANSLATE_H_
#define TRANSLATE_H_

#include <hitable.h>

class Translate : public Hitable {
public:
    Hitable *hitable;
    vec3 move;

    Translate(Hitable *hit, const vec3 &m) : hitable(hit), move(m) {}
    bool hit(const ray &r, float tmin, float tmax, HitResult &hitResult) const {
        ray moved_r(r.origin() - move, r.direction(), r.time());
        if (hitable->hit(moved_r, tmin, tmax, hitResult)) {
            hitResult.p += move;
            return true;
        }
        else {
            return false;
        }
    }
    bool bounding_box(float t0, float t1, AABB &box) const {
        if (hitable->bounding_box(t0, t1, box)) {
            box.min += move;
            box.max += move;
            return true;
        }
        else {
            return false;
        }
    }
};

#endif