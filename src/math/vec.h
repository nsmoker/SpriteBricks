#pragma once

class Vec {
    public:
    float x;
    float y;
    float z;
    Vec(float vx, float vy, float vz);
    Vec(float vx, float vy);
    Vec(float v);
    Vec();

    float magnitude();
    float dot(const Vec& other);

    Vec operator+(const Vec& other);
    Vec operator+(const float& scalar);
    Vec operator-(const Vec& other);
    Vec operator-(const float& scalar);
    Vec operator*(const Vec& other);
    Vec operator*(const float& scalar);
    Vec operator/(const Vec& other);
    Vec operator/(const float& scalar);

    Vec normalized();
};