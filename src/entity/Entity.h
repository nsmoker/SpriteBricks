#pragma once

#include <vector>
#include "Component.h"
#include "game/game.h"

namespace engine {
    class Entity {
        private:
            int id;
            std::vector<Component*> components;
        public:
            Entity();
            inline void init() {
                for (int i = 0; i < components.size(); ++i) {
                    components[i]->init(*this);
                }
            }

            inline void update() {
                for (int i = 0; i < components.size(); ++i) {
                    components[i]->update(*this);
                }
            }

            inline void atDraw() {
                for (int i = 0; i < components.size(); ++i) {
                    components[i]->atDraw(*this);
                }
            }

            inline int getId() const { return id; };
            inline void setId(int _id) { id = _id; }

            template <class T>
            T* getComponent() {
                for (int i = 0; i < components.size(); ++i) {
                    Component* component = components[i];
                    if (dynamic_cast<T*>(component) != nullptr) {
                        return dynamic_cast<T*>(component);
                    }
                }

                return nullptr;
            }

            template <class T>
            T* addComponent() {
                T* component = new T();
                if (!std::is_base_of<Component, T>::value) {
                    SDL_Log("Warning: ignoring addition of component of type %s because it is not a component type. Returned nullptr.", typeid(component).name());
                    return nullptr;
                } else {
                    components.push_back(component);
                    return component;
                }
            }

            ~Entity();
    };
}