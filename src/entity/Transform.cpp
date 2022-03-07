#include "Transform.h"

namespace engine {

    void to_json(nlohmann::json& j, const Transform& transform) {
        j = nlohmann::json{{"position", transform.position}, {"scale", transform.scale}, {"rotation", transform.rotationEuler}};
        j["decorator"] = "transform";
    }

    void from_json(const nlohmann::json& j, Transform& transform) {
        j.at("position").get_to(transform.position);
        j.at("scale").get_to(transform.scale);
        j.at("rotation").get_to(transform.rotationEuler);
    }

    std::string Transform::serialize() { 
        auto j = nlohmann::json();
        j["decorator"] = "transform";
        to_json(j, *this);
        return j.dump();
     }
}