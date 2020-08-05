#ifndef CONSTANT_MEDIUM_H_
#define CONSTANT_MEDIUM_H_

#include <hitable.h>
#include <texture.h>
#include <cfloat>
#include <material/isotropic.h>

class constant_medium : public Hitable {
public:
    Hitable *boundary;
    float density;
    Material *material;
    
    constant_medium(Hitable *b, float d, Texture *tex) : boundary(b), density(d), material(new isotropic(tex)) {};
    bool hit(const ray &r, float tmin, float tmax, HitResult &hitResult) const;
    bool bounding_box(float t0, float t1, AABB &box) const {
        return boundary->bounding_box(t0, t1, box);
    }
};

bool constant_medium::hit(const ray &r, float tmin, float tmax, HitResult &rec) const {
    HitResult rec1, rec2;
    if (boundary->hit(r, -FLT_MAX, FLT_MAX, rec1)) {
        if (boundary->hit(r, rec1.t + 0.001, FLT_MAX, rec2)) {
            if (rec1.t < tmin) {
                rec1.t = tmin;
            }
            if (rec2.t > tmax) {
                rec2.t = tmax;
            }
            if (rec1.t >= rec2.t) {
                return false;
            }
            if (rec1.t < 0) {
                rec1.t = 0;
            }
            float distance = (rec2.t - rec1.t) * length(r.direction());
            float hit_distance = -(1 / density) * log(getrand(seed));
            if (hit_distance < distance) {
                rec.t = rec1.t + hit_distance / length(r.direction());
                rec.p = r(rec.t);
                rec.mateial = material;
                return true;
            }
        }
    }
    return false;
};

#endif