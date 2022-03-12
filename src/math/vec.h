#pragma once

#include <external/json.hpp>

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

        void set(float _x, float _y, float _z);

        float magnitude() const;

        float dot(const Vec &other) const;

        Vec operator+(const Vec &other) const;

        Vec operator+(const float &scalar) const;

        Vec& operator+=(const Vec& other);

        Vec& operator+=(const float& scalar);

        Vec operator-(const Vec &other) const;

        Vec operator-(const float &scalar) const;

        Vec& operator-=(const Vec& other);

        Vec& operator-=(const float& scalar);

        Vec operator*(const Vec &other) const;

        Vec operator*(const float &scalar) const;

        Vec& operator*=(const Vec& other);

        Vec& operator*=(const float& scalar);

        Vec operator/(const Vec &other) const;

        Vec operator/(const float &scalar) const;

        Vec& operator/=(const Vec& other);

        Vec& operator/=(const float& scalar);

        Vec normalized() const;
    };

    using json = nlohmann::json;
    void to_json(json& j, const Vec& vec);
    void from_json(const json& j, Vec& vec);
}