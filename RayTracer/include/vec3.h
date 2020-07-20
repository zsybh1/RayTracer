#ifndef VEC3_H_
#define VEC3_H_

#include <cmath>
#include <iostream>

class vec3 {
private:
    float e[3];

public:
    vec3() {}
    vec3(float x) { e[0] = e[1] = e[2] = x; }
    vec3(float e0, float e1, float e2) { e[0] = e0; e[1] = e1; e[2] = e2;}

    float &x() { return e[0]; }
    float x() const { return e[0]; }
    float &y() { return e[1]; }
    float y() const { return e[1]; }
    float &z() { return e[2]; }
    float z() const { return e[2]; }
    float &r() { return e[0]; }
    float r() const { return e[0]; }
    float &g() { return e[1]; }
    float g() const { return e[1]; }
    float &b() { return e[2]; }
    float b() const { return e[2]; }

    float operator[](int i) const { return e[i]; }
    float &operator[](int i) { return e[i]; }

    vec3 operator+() const { return *this; }
    vec3 operator-() const { return *this * -1.0f; }

    friend float length(const vec3 &v);
    friend float squared_length(const vec3 &v);
    friend vec3 unit(const vec3 &v);
    void make_unit();

    const vec3 operator+(const vec3 &v) const;
    const vec3 operator-(const vec3 &v) const;
    const vec3 operator*(const vec3 &v) const;
    const vec3 operator/(const vec3 &v) const;
    const vec3 operator*(float f) const;
    const vec3 operator/(float f) const;
    friend const vec3 operator*(float f, const vec3 &v);

    vec3 &operator+=(const vec3 &v);
    vec3 &operator-=(const vec3 &v);
    vec3 &operator*=(const vec3 &v);
    vec3 &operator/=(const vec3 &v);
    vec3 &operator*=(float f);
    vec3 &operator/=(float f);

    friend float dot(const vec3 &u, const vec3 &v);
    friend vec3 cross(const vec3 &u, const vec3 &v);
    friend vec3 reflect(const vec3 &v, const vec3 &n);
    friend bool refract(const vec3 &v, const vec3 &n, float rate, vec3 &refracted);

    friend std::istream &operator>>(std::istream &in, vec3 &v);
    friend std::ostream &operator<<(std::ostream &out, const vec3 &v);
};

inline float length(const vec3 &v) {
    return std::sqrt(squared_length(v));
}
inline float squared_length(const vec3 &v) {
    return dot(v, v);
}
inline vec3 unit(const vec3 &v) {
    return v / length(v);
}
inline void vec3::make_unit() {
    *this = unit(*this);
}

inline const vec3 vec3::operator+(const vec3 &v) const {
    return vec3(e[0] + v[0], e[1] + v[1], e[2] + v[2]);
}
inline const vec3 vec3::operator-(const vec3 &v) const {
    return vec3(e[0] - v[0], e[1] - v[1], e[2] - v[2]);
}
inline const vec3 vec3::operator*(const vec3 &v) const {
    return vec3(e[0] * v[0], e[1] * v[1], e[2] * v[2]);
}
inline const vec3 vec3::operator/(const vec3 &v) const {
    return vec3(e[0] / v[0], e[1] / v[1], e[2] / v[2]);
}
inline const vec3 vec3::operator*(float f) const {
    return vec3(e[0] * f, e[1] * f, e[2] * f);
}
inline const vec3 vec3::operator/(float f) const {
    return vec3(e[0] / f, e[1] / f, e[2] / f);
}
inline const vec3 operator*(float f, const vec3 &v) {
    return vec3(v[0] * f, v[1] * f, v[2] * f);
}

inline vec3 &vec3::operator+=(const vec3 &v) {
    e[0] += v[0];
    e[1] += v[1];
    e[2] += v[2];
    return *this;
}
inline vec3 &vec3::operator-=(const vec3 &v) {
    e[0] -= v[0];
    e[1] -= v[1];
    e[2] -= v[2];
    return *this;
}
inline vec3 &vec3::operator*=(const vec3 &v) {
    e[0] *= v[0];
    e[1] *= v[1];
    e[2] *= v[2];
    return *this;
}
inline vec3 &vec3::operator/=(const vec3 &v) {
    e[0] /= v[0];
    e[1] /= v[1];
    e[2] /= v[2];
    return *this;
}
inline vec3 &vec3::operator*=(float f) {
    e[0] *= f;
    e[1] *= f;
    e[2] *= f;
    return *this;
}
inline vec3 &vec3::operator/=(float f) {
    e[0] /= f;
    e[1] /= f;
    e[2] /= f;
    return *this;
}

inline float dot(const vec3 &u, const vec3 &v) {
    return u[0] * v[0] + u[1] * v[1] + u[2] * v[2];
}
inline vec3 cross(const vec3 &u, const vec3 &v) {
    return vec3(u[1] * v[2] - u[2] * v[1], u[2] * v[0] - u[0] * v[2],
                u[0] * v[1] - u[1] * v[0]);
}
inline vec3 reflect(const vec3 &v, const vec3 &n) {
    return v - 2.0f * dot(v, n) * n;
}
inline bool refract(const vec3 &v, const vec3 &n, float rate, vec3 &refracted) {
    float len_v = length(v);
    vec3 unit_v = v / len_v;
    float cos = dot(unit_v, n);
    float delta = 1.0f - rate * rate * (1 - cos * cos);
    if (delta > 0) {
        refracted = (rate * (unit_v - cos * n) - n * sqrt(delta)) * len_v;
        return true;
    }
    return false;
}

inline std::istream &operator>>(std::istream &in, vec3 &v) {
    in >> v[0] >> v[1] >> v[2];
    return in;
}
inline std::ostream &operator<<(std::ostream &out, const vec3 &v) {
    out << v[0] << v[1] << v[2];
    return out;
}

#endif