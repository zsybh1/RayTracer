#ifndef RAY_H_
#define RAY_H_

#include <vec3.h>

class ray{
private:
    vec3 e;
    vec3 d;
    float _time;

public:
    ray() {}
    ray(const vec3 &E, const vec3 &D, float t = 0.0f) : e(E), d(D), _time(t) {}

    const vec3 &origin() const { return e; }
    const vec3 &direction() const { return d; }
    vec3 operator()(float t) const { return e + t * d;}
    float time() const { return _time; }
};

#endif