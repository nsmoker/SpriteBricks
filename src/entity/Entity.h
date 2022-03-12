#pragma once

#include <vector>
#include "Component.h"
#include "SDL_log.h"
#include "game/game.h"
#include <external/json.hpp>

namespace engine {
    class Entity {
        private:
            int id;
            std::vector<Component*> components;
        public:
            std::string name;
            
            inline const static std::string componentArrayDecorator = "Component";
            inline const static std::string jObjectDecorator = "Entity";

            Entity(std::string _name): name(_name) {}
            inline std::vector<Component*> getComponents() const { return components; }
            void init();

            void update();

            void atDraw();

            inline int getId() const { return id; };
            inline void setId(int _id) { id = _id; }

            template <class T>
            T* getComponent();

            template <class T>
            T& addComponent();

            ~Entity();
    };

    template <class T>
    T* Entity::getComponent() {
        for (int i = 0; i < components.size(); ++i) {
            Component* component = components[i];
            if (dynamic_cast<T*>(component) != nullptr) {
                return dynamic_cast<T*>(component);
            }
        }

        return nullptr;
    }

    template <class T>
    T& Entity::addComponent() {
        T* component = new T();
        if (!std::is_base_of<Component, T>::value) {
            SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
                "Ignoring addition of component of type %s because it is not a component type. Returned reference is invalid.", typeid(component).name());
            return *component;
        } else {
            components.push_back(component);
            return *component;
        }
    }

    void to_json(nlohmann::json& j, const Entity& entity);
}