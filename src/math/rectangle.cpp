#include "rectangle.h"
#include "../external/json.hpp"

namespace engine {
    using json = nlohmann::json;

    void to_json(json& j, const Rectangle& rectangle) {
        j = json{{"w", rectangle.w}, {"h", rectangle.h}, {"x", rectangle.x}, {"y", rectangle.y}};
    }

    void from_json(const json& j, Rectangle& rectangle) {
        j.at("w").get_to(rectangle.w);
        j.at("h").get_to(rectangle.h);
        j.at("x").get_to(rectangle.x);
        j.at("y").get_to(rectangle.y);
    }

    Rectangle::Rectangle() = default;

    Rectangle::Rectangle(float _w, float _h, float _x, float _y) {
        w = _w;
        h = _h;
        x = _x;
        y = _y;
    }

    bool Rectangle::contains(const Vec &point) const {
        bool horizontallyContained = point.x <= x + w && point.x >= x;
        bool verticallyContained = point.y >= y && point.y <= y + h;
        return horizontallyContained && verticallyContained;
    }

    bool Rectangle::intersects(const Rectangle &other) const {
        bool isBelow = other.top_left().y > bottom_right().y;
        bool isAbove = top_left().y > other.bottom_right().y;
        bool isLeft = other.bottom_right().x < top_left().x;
        bool isRight = other.top_left().x > bottom_right().x;
        bool ret = !((isBelow && isLeft) || (isBelow && isRight) || (isAbove && isLeft) || (isAbove && isRight));
        return ret;
    }
}