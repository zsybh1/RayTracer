#ifndef ROTATE_H_
#define ROTATE_H_

#include <hitable.h>

class Rotate_y : public Hitable {
public:
    Hitable *hitable;
    float sin_theta;
    float cos_theta;

    Rotate_y(Hitable *hit, float angle);
    bool hit(const ray &r, float tmin, float tmax, HitResult &rec) const;
    bool bounding_box(float t0, float t1, AABB &box) const;
};

Rotate_y::Rotate_y(Hitable *hit, float angle) : hitable(hit) {
    float pi = acos(-1.0f);
    float theta = (pi / 180.0f) * angle;
    sin_theta = sin(theta);
    cos_theta = cos(theta);
}
bool Rotate_y::hit(const ray &r, float tmin, float tmax, HitResult &rec) const {
    vec3 origin = r.origin();
    vec3 direction = r.direction();
    origin.x() = cos_theta * r.origin().x() - sin_theta * r.origin().z();
    origin.z() = sin_theta * r.origin().x() + cos_theta * r.origin().z();
    direction.x() = cos_theta * r.direction().x() - sin_theta * r.direction().z();
    direction.z() = sin_theta * r.direction().x() + cos_theta * r.direction().z();
    ray rotated_r(origin, direction, r.time());
    if (hitable->hit(rotated_r, tmin, tmax, rec)) {
        vec3 p = rec.p;
        vec3 normal = rec.normal;
        p.x() = cos_theta * rec.p.x() + sin_theta * rec.p.z();
        p.z() = -sin_theta * rec.p.x() + cos_theta * rec.p.z();
        normal.x() = cos_theta * rec.normal.x() + sin_theta * rec.normal.z();
        normal.z() = -sin_theta * rec.normal.x() + cos_theta * rec.normal.z();
        rec.p = p;
        rec.normal = normal;
        return true;
    }
    else {
        return false;
    }
}
bool Rotate_y::bounding_box(float t0, float t1, AABB &box) const {
    if(hitable->bounding_box(t0, t1, box)) {
        vec3 min = box.min;
        vec3 max = box.max;
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                float x = i * max.x() + (1-i) * min.x();
                float z = j * max.z() + (1-j) * min.z();
                vec3 newbox;
                newbox.x() = cos_theta * x + sin_theta * z;
                newbox.z() = -sin_theta * z + cos_theta * x;
                for (int k : {0, 2}) {
                    if (newbox[k] > box.max[k]) {
                        box.max[k] = newbox[k];
                    }
                    if (newbox[k] < box.min[k]) {
                        box.min[k] = newbox[k];
                    }
                }
            }
        }
        return true;
    }
    else {
        return false;
    }
}

#endif