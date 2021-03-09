#pragma once
#include <utility>

namespace engine {
    class Rectangle {
        private:
            float _w;
            float _h;
            float _x;
            float _y;
        public:
            Rectangle();
            Rectangle(float w, float h, float x, float y);
            [[nodiscard]] inline float width() const { return _w; }
            inline void setWidth(float w) { _w = w; }
            [[nodiscard]] inline float height() const {return _h; }
            inline void setHeight(float h) { _h = h; }
            [[nodiscard]] inline float posX() const { return _x; }
            inline void setX(float x) { _x = x; }
            [[nodiscard]] inline float posY() const { return _y; }
            inline void setY(float y) { _y = y; }
            [[nodiscard]] inline float area() const { return _w * _h; }
            inline std::pair<float, float> top_left() { return std::pair { _x, _y + _h}; }
            [[nodiscard]] inline std::pair<float, float> bottom_right() const { return std::pair { _x + _w, _y}; }
    };
}