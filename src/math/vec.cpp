#include "vec.h"
#include <cmath>
#include "../external/json.hpp"

namespace engine {
    using json = nlohmann::json;

    void to_json(json& j, const Vec& vec) {
        j = json{{"x", vec.x}, {"y", vec.y}, {"z", vec.z}};
    }

    void from_json(const json& j, Vec& vec) {
        j.at("x").get_to(vec.x);
        j.at("y").get_to(vec.y);
        j.at("z").get_to(vec.z);
    }

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

    Vec& Vec::operator+=(const Vec &other) {
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;
        return *this;
    }

    Vec& Vec::operator+=(const float& other) {
        this->x += other;
        this->y += other;
        this->z += other;
        return *this;
    }

    Vec Vec::operator-(const Vec &other) const {
        Vec ret(x - other.x, y - other.y, z - other.z);
        return ret;
    }

    Vec Vec::operator-(const float &scalar) const {
        Vec ret(x - scalar, y - scalar, z - scalar);
        return ret;
    }

    Vec& Vec::operator-=(const Vec &other) {
        this->x -= other.x;
        this->y -= other.y;
        this->z -= other.z;
        return *this;
    }

    Vec& Vec::operator-=(const float& other) {
        this->x -= other;
        this->y -= other;
        this->z -= other;
        return *this;
    }

    Vec Vec::operator*(const Vec &other) const {
        Vec ret(x * other.x, y * other.y, z * other.z);
        return ret;
    }

    Vec Vec::operator*(const float &scalar) const {
        Vec ret(x * scalar, y * scalar, z * scalar);
        return ret;
    }

    Vec& Vec::operator*=(const Vec &other) {
        this->x *= other.x;
        this->y *= other.y;
        this->z *= other.z;
        return *this;
    }

    Vec& Vec::operator*=(const float& other) {
        this->x *= other;
        this->y *= other;
        this->z *= other;
        return *this;
    }

    Vec Vec::operator/(const Vec &other) const {
        Vec ret(x / other.x, y / other.y, z / other.z);
        return ret;
    }

    Vec Vec::operator/(const float &scalar) const {
        Vec ret(x / scalar, y / scalar, z / scalar);
        return ret;
    }

    Vec& Vec::operator/=(const Vec &other) {
        this->x /= other.x;
        this->y /= other.y;
        this->z /= other.z;
        return *this;
    }

    Vec& Vec::operator/=(const float& other) {
        this->x /= other;
        this->y /= other;
        this->z /= other;
        return *this;
    }

    Vec Vec::normalized() const {
        float mag = magnitude();
        return *this / mag;
    }
}