#pragma once

namespace engine {
    class Entity;

    class Component {
        public: 
            virtual void init(Entity& entity) {}
            virtual void update(Entity& entity) {}
            virtual void atDraw(Entity& entity) {}
    };
}