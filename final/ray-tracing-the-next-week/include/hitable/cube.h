#ifndef CUBE_H_
#define CUBE_H_

#include <hitable.h>
#include <hitable/hitlist.h>
#include <hitable/flip_normal.h>
#include <hitable/rectangular.h>


class Cube : public Hitable {
public:
    vec3 min, max;
    HitableList list;

    Cube(vec3 _min, vec3 _max, Material *mat);
    bool hit(const ray &r, float tmin, float tmax, HitResult &hitResult) const {
        return list.hit(r, tmin, tmax, hitResult);
    }
    bool bounding_box(float t0, float t1, AABB &box) const {
        box = AABB(min, max);
        return true;
    }
};

Cube::Cube(vec3 _min, vec3 _max, Material *mat) : min(_min), max(_max) {
    list.add(new Filp_normal(new xz_rect(min.x(), min.z(), max.x(), max.z(), min.y(), mat)));
    list.add(new xz_rect(min.x(), min.z(), max.x(), max.z(), max.y(), mat));
    list.add(new Filp_normal(new xy_rect(min.x(), min.y(), max.x(), max.y(), min.z(), mat)));
    list.add(new xy_rect(min.x(), min.y(), max.x(), max.y(), max.z(), mat));
    list.add(new Filp_normal(new yz_rect(min.y(), min.z(), max.y(), max.z(), min.x(), mat)));
    list.add(new yz_rect(min.y(), min.z(), max.y(), max.z(), max.x(), mat));
}

#endif