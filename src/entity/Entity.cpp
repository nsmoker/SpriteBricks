#include "Entity.h"
#include <typeinfo>
#include "Transform.h"
#include "entity/Component.h"

namespace engine {
    void Entity::init() {
        for (int i = 0; i < components.size(); ++i) {
            components[i]->init(*this);
        }
    }

    void Entity::update() {
        for (int i = 0; i < components.size(); ++i) {
            components[i]->update(*this);
        }
    }

    void Entity::atDraw() {
        for (int i = 0; i < components.size(); ++i) {
            Component& c = *components[i];
            components[i]->atDraw(*this);
        }
    }

    void to_json(nlohmann::json& j, const Entity& entity) {
        auto jsonArray = json::array();
        j["decorator"] = Entity::jObjectDecorator;
        j["Name"] = entity.name;
        std::vector<Component*> comps = entity.getComponents();
        for (int i = 0; i < comps.size(); ++i) {
            jsonArray.push_back(comps[i]->serialize());
        }
        j[Entity::componentArrayDecorator] = jsonArray;
    }

    Entity::~Entity() {
        for (int i = 0; i < components.size(); ++i) {
            delete components[i];
        }
    }
}