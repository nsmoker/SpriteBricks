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
}