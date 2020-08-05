#ifndef CAMERA_H_
#define CAMERA_H_

#include <ray.h>
#include <cmath>
#include <random.h>

class Camera {
public:
    vec3 origin;
    vec3 zeroPoint;
    vec3 up;
    vec3 right;
    vec3 u, v, w;
    float dof;
    float time0, time1;

    Camera(vec3 lookfrom, vec3 lookat, vec3 worldup, float fov, float aspect, float dof_2, float t0, float t1) : time0(t0), time1(t1) {
        dof = dof_2 / 2;
        float theta = fov * acos(-1.0f) / 180.0f;
        float half_height = tan(theta / 2.0f);
        float half_width = half_height * aspect;
        float distance = length(lookfrom - lookat);
        w = unit(lookfrom - lookat);
        u = unit(cross(worldup, w));
        v = cross(w, u);
        origin = lookfrom;
        zeroPoint = origin - distance * (half_height * v + half_width * u + w);
        up = 2.0f * half_height * distance * v;
        right = 2.0f * half_width * distance * u;
    }
    ray get_ray(float s, float t) {
        vec3 p = dof * random_point_in_unit_circle();
        vec3 offset = u * p.x() + v * p.y();
        float now = time0 + getrand(seed) * (time1 - time0); 
        return ray(origin + offset, zeroPoint + s * right + t * up - origin - offset, now);
    }
};

#endif