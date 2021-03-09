#include "vec.h"
#include <cmath>

namespace engine {
    Vec::Vec(float vx, float vy, float vz) {
        x = vx;
        y = vy;
        z = vz;
    }

    Vec::Vec(float vx, float vy) {
        x = vx;
        y = vy;
        z = 0.0f;
    }

    Vec::Vec(float v) {
        x = v;
        y = v;
        z = v;
    }

    Vec::Vec() {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
    }

    float Vec::magnitude() const {
        return sqrtf(x * x + y * y + z * z);
    }

    float Vec::dot(const Vec &other) const {
        return other.x * x + other.y * y + other.z * z;
    }

    Vec Vec::operator+(const Vec &other) const {
        Vec ret(other.x + x, other.y + y, other.z + z);
        return ret;
    }

    Vec Vec::operator+(const float &scalar) const {
        Vec ret(x + scalar, y + scalar, z + scalar);
        return ret;
    }

    Vec Vec::operator-(const Vec &other) const {
        Vec ret(x - other.x, y - other.y, z - other.z);
        return ret;
    }

    Vec Vec::operator-(const float &scalar) const {
        Vec ret(x - scalar, y - scalar, z - scalar);
        return ret;
    }

    Vec Vec::operator*(const Vec &other) const {
        Vec ret(x * other.x, y * other.y, z * other.z);
        return ret;
    }

    Vec Vec::operator*(const float &scalar) const {
        Vec ret(x * scalar, y * scalar, z * scalar);
        return ret;
    }

    Vec Vec::operator/(const Vec &other) const {
        Vec ret(x / other.x, y / other.y, z / other.z);
        return ret;
    }

    Vec Vec::operator/(const float &scalar) const {
        Vec ret(x / scalar, y / scalar, z / scalar);
        return ret;
    }

    Vec Vec::normalized() const {
        float mag = magnitude();
        return *this / mag;
    }
}