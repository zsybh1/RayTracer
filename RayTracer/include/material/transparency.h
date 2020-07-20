#ifndef TRANSPARENCY_H_
#define TRANSPARENCY_H_

#include <material.h>
#include <random.h>

float schlick(float cosine, float rate) {
    float r0 = (1 - rate) / (1 + rate);
    r0 = r0 * r0;
    return r0 + (1-r0) * pow((1-cosine), 5);
}

class Transparency : public Material {
public:
    vec3 albedo;
    float object_rate;

    Transparency(float r, const vec3 &a = vec3(1.0f)) : albedo(a), object_rate(r) {}
    bool scatter(const ray &r, const HitResult &rec, vec3 &attenuation, ray &next) const {
        vec3 normal;
        float rate;
        attenuation = albedo;
        float p_reflect;
        float cosine;
        if (dot(r.direction(), rec.normal) > 0.0f) {
            normal = -rec.normal;
            rate = object_rate;
            cosine = object_rate * dot(r.direction(), rec.normal) / length(r.direction());
        } else {
            normal = rec.normal;
            rate = 1.0f / object_rate;
            cosine = -dot(r.direction(), rec.normal) / length(r.direction());
        }
        vec3 refracted;
        if (refract(r.direction(), normal, rate, refracted)) {
            p_reflect = schlick(cosine, object_rate);
        }
        else {
            p_reflect = 1.0f;
        }
        if (getrand(seed) < p_reflect) {
            next = ray(rec.p, reflect(r.direction(), rec.normal));
        }
        else {
            next = ray(rec.p, refracted);
        }
        return true;
    }
};

#endif