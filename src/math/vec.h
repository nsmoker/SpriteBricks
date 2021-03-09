#pragma once

namespace engine {
    class Vec {
    public:
        float x;
        float y;
        float z;

        Vec(float vx, float vy, float vz);

        Vec(float vx, float vy);

        Vec(float v);

        Vec();

        float magnitude() const;

        float dot(const Vec &other) const;

        Vec operator+(const Vec &other) const;

        Vec operator+(const float &scalar) const;

        Vec operator-(const Vec &other) const;

        Vec operator-(const float &scalar) const;

        Vec operator*(const Vec &other) const;

        Vec operator*(const float &scalar) const;

        Vec operator/(const Vec &other) const;

        Vec operator/(const float &scalar) const;

        Vec normalized() const;
    };
}