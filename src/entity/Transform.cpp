#include "Transform.h"

namespace engine {

    void to_json(nlohmann::json& j, const Transform& transform) {
        j = nlohmann::json{{"position", transform.position}, {"scale", transform.scale}, {"rotation", transform.rotationEuler}};
        j["decorator"] = Transform::jObjectDecorator;
    }

    nlohmann::json Transform::serialize() {
        auto j = nlohmann::json();
        j["decorator"] = jObjectDecorator;
        to_json(j, *this);
        return j;
     }
}