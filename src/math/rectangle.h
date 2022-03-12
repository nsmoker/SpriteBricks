#pragma once
#include "math/vec.h"
#include <utility>
#include <external/json.hpp>

namespace engine {

    class Rectangle {
        private:
        public:
            Rectangle();
            float w;
            float h;
            float x;
            float y;
            Rectangle(float w, float h, float x, float y);
            [[nodiscard]] inline float area() const { return w * h; }
            [[nodiscard]] inline Vec top_left() const { return Vec(x, y + h); }
            [[nodiscard]] inline Vec bottom_right() const { return Vec(x + w, y); }

            bool contains(const Vec& point) const;
            bool intersects(const Rectangle& other) const;
    };

    using json = nlohmann::json;
    void to_json(json& j, const Rectangle& rectangle);
    void from_json(const json& j, Rectangle& rectangle);
}