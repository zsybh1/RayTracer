#ifndef RANDOM_H_
#define RANDOM_H_

#include <ctime>
#include <random>

std::default_random_engine seed(time(0));
std::uniform_real_distribution<float> getrand(0, 1);

vec3 random_point_in_unit_sphere() {
    vec3 p;
    do {
        p = 2.0f * vec3(getrand(seed), getrand(seed), getrand(seed)) -
            vec3(1.0f);
    } while (squared_length(p) >= 1.0f);
    return p;
}

vec3 random_point_in_unit_circle() {
    vec3 p;
    do {
        p = 2.0f * vec3(getrand(seed), getrand(seed), 0.0f) - vec3(1.0f, 1.0f, 0.0f);
    } while (squared_length(p) >= 1.0f);
    return p;
}

#endif