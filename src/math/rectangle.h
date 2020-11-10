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
            Rectangle(float w, float h, float x, float y);
            inline float width() const { return _w; }
            inline void setWidth(float w) { _w = w; }
            inline float height() const {return _h; }
            inline void setHeight(float h) { _h = h; }
            inline float posX() const { return _x; }
            inline void setX(float x) { _x = x; }
            inline float posY() const { return _y; }
            inline void setY(float y) { _y = y; }
            inline float area() { return _w * _h; }
            inline std::pair<int, int> top_left() { return std::pair { _x, _y}; }
            inline std::pair<int, int> bottom_right() const { return std::pair { _x + _w, _y + _h}; }
    };
}