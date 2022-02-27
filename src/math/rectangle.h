#pragma once
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
            inline std::pair<float, float> top_left() { return std::pair { x, y + h}; }
            [[nodiscard]] inline std::pair<float, float> bottom_right() const { return std::pair { x + w, y}; }
    };

    using json = nlohmann::json;
    void to_json(json& j, const Rectangle& rectangle);
    void from_json(const json& j, Rectangle& rectangle);
}