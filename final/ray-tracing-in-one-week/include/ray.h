#ifndef RAY_H_
#define RAY_H_

#include <vec3.h>

class ray{
private:
    vec3 e;
    vec3 d;

public:
    ray() {}
    ray(const vec3 &E, const vec3 &D) { e = E; d = D; }

    const vec3 &origin() const { return e; }
    const vec3 &direction() const { return d; }
    vec3 operator()(float t) const { return e + t * d;}
};

#endif