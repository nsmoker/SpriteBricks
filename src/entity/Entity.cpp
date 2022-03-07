#include "Entity.h"
#include <typeinfo>
#include "Transform.h"

namespace engine {
    void to_json(nlohmann::json& j, const Entity& entity) {
        auto jsonArray = json::array();
        j["decorator"] = "entity";
        std::vector<Component*> comps = entity.getComponents();
        for (int i = 0; i < comps.size(); ++i) {
            jsonArray.push_back(comps[i]->serialize());
        }
        j["components"] = jsonArray;
    }

    Entity::Entity(): id(-1) {
        addComponent<Transform>();
    }

    Entity::~Entity() {
        for (int i = 0; i < components.size(); ++i) {
            delete components[i];
        }
    }
}