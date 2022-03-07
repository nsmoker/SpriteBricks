#pragma once
#include <external/json.hpp>
#include <string>

namespace engine {
    class Entity;

    class Component {
        public: 
            virtual void init(Entity& entity) {}
            virtual void update(Entity& entity) {}
            virtual void atDraw(Entity& entity) {}
            virtual std::string serialize() = 0;
            virtual void drawEditor() {}
            virtual ~Component() {};
    };
}