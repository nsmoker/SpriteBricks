#include "rectangle.h"

namespace engine {
    Rectangle::Rectangle() = default;

    Rectangle::Rectangle(float w, float h, float x, float y) {
        _w = w;
        _h = h;
        _x = x;
        _y = y;
    }
}