#ifndef RECTANGULAR_H_
#define RECTANGULAR_H_

#include <hitable.h>

class xy_rect : public Hitable {
public:
    float x0, y0, x1, y1, z;
    Material *material;

    xy_rect(float _x0, float _y0, float _x1, float _y1, float _z, Material *mat)
        : x0(_x0), x1(_x1), y0(_y0), y1(_y1), z(_z), material(mat) {}

    bool hit(const ray &r, float tmin, float tmax, HitResult &hitResult) const;
    bool bounding_box(float t0, float t1, AABB &box) const {
        box = AABB(vec3(x0, y0, z - 0.0001f), vec3(x1, y1, z + 0.0001f));
        return true;
    }
};

class xz_rect : public Hitable {
public:
    float x0, z0, x1, z1, y;
    Material *material;

    xz_rect(float _x0, float _z0, float _x1, float _z1, float _y, Material *mat)
        : x0(_x0), x1(_x1), z0(_z0), z1(_z1), y(_y), material(mat) {}

    bool hit(const ray &r, float tmin, float tmax, HitResult &hitResult) const;
    bool bounding_box(float t0, float t1, AABB &box) const {
        box = AABB(vec3(x0, y - 0.0001f, z0), vec3(x1, y + 0.0001f, z1));
        return true;
    }
};

class yz_rect : public Hitable {
public:
    float y0, z0, y1, z1, x;
    Material *material;

    yz_rect(float _y0, float _z0, float _y1, float _z1, float _x, Material *mat)
        : y0(_y0), y1(_y1), z0(_z0), z1(_z1), x(_x), material(mat) {}

    bool hit(const ray &r, float tmin, float tmax, HitResult &hitResult) const;
    bool bounding_box(float t0, float t1, AABB &box) const {
        box = AABB(vec3(x - 0.0001f, y0, z0), vec3(x + 0.0001f, y1, z1));
        return true;
    }
};

bool xy_rect::hit(const ray &r, float tmin, float tmax,
                  HitResult &hitResult) const {
    float t = (z - r.origin().z()) / r.direction().z();
    if (t < tmin || t > tmax) {
        return false;
    }
    float x = r.origin().x() + t * r.direction().x();
    float y = r.origin().y() + t * r.direction().y();
    if (x < x0 || x > x1 || y < y0 || y > y1) {
        return false;
    }
    hitResult.t = t;
    hitResult.mateial = material;
    hitResult.normal = vec3(0.0f, 0.0f, 1.0f);
    hitResult.p = r(t);
    hitResult.u = (x - x0) / (x1 - x0);
    hitResult.v = (y - y0) / (y1 - y0);
    return true;
}

bool xz_rect::hit(const ray &r, float tmin, float tmax,
                  HitResult &hitResult) const {
    float t = (y - r.origin().y()) / r.direction().y();
    if (t < tmin || t > tmax) {
        return false;
    }
    float x = r.origin().x() + t * r.direction().x();
    float z = r.origin().z() + t * r.direction().z();
    if (x < x0 || x > x1 || z < z0 || z > z1) {
        return false;
    }
    hitResult.t = t;
    hitResult.mateial = material;
    hitResult.normal = vec3(0.0f, 1.0f, 0.0f);
    hitResult.p = r(t);
    hitResult.u = (x - x0) / (x1 - x0);
    hitResult.v = (z - z0) / (z1 - z0);
    return true;
}

bool yz_rect::hit(const ray &r, float tmin, float tmax,
                  HitResult &hitResult) const {
    float t = (x - r.origin().x()) / r.direction().x();
    if (t < tmin || t > tmax) {
        return false;
    }
    float y = r.origin().y() + t * r.direction().y();
    float z = r.origin().z() + t * r.direction().z();
    if (y < y0 || y > y1 || z < z0 || z > z1) {
        return false;
    }
    hitResult.t = t;
    hitResult.mateial = material;
    hitResult.normal = vec3(1.0f, 0.0f, 0.0f);
    hitResult.p = r(t);
    hitResult.u = (y - y0) / (y1 - y0);
    hitResult.v = (z - z0) / (z1 - z0);
    return true;
}

#endif