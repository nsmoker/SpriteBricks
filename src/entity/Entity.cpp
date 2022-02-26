#include "Entity.h"
#include <typeinfo>
#include "Transform.h"

namespace engine {
    Entity::Entity(): id(-1) {
        addComponent<Transform>();
    }

    template <class T>
    void Entity::addComponent() {
        T component;
        if (!std::is_base_of<Component, T>::value) {
            SDL_Log("Warning: ignoring addition of component of type %s because it is not a component type.", typeid(component).name());
        } else {
            components.emplace_back();
        }
    }

    template <class T>
    Component& Entity::getComponent() {
        for (int i = 0; i < components.size(); ++i) {
            Component& component = components[i];
            if (dynamic_cast<T&>(component) != nullptr) {
                return dynamic_cast<T&>(component);
            }
        }

        return nullptr;
    }
}