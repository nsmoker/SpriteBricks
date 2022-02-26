#pragma once

#include <vector>
#include "Component.h"
#include "game/game.h"

namespace engine {
    class Entity {
        private:
            int id;
            std::vector<Component> components;
        public:
            Entity();
            inline int getId() const { return id; };
            inline void setId(int _id) { id = _id; }
            template <class T>
            Component &getComponent();
            template <class T>
            void addComponent();
    };
}