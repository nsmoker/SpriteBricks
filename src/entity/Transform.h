#pragma once

#include <entity/Component.h>
#include <math/vec.h>

namespace engine {
    class Transform : public Component {
        private: 
            engine::Vec position;
            engine::Vec scale;
            engine::Vec rotationEuler;
        public:
            void init(Entity& entity) {}
            void update(Entity& entity) {}
            void atDraw(Entity& entity) {}

            inline engine::Vec getPosition() const { return position; }

            inline engine::Vec getScale() const { return scale; }

            inline engine::Vec getRotation() const { return rotationEuler; }

            inline void setPosition(const engine::Vec newPosition) { position = newPosition; }

            inline void setPosition(float x, float y, float z) { 
                position.x = x;
                position.y = y;
                position.z = z;
            }
            
            inline void setPosition(float x, float y) {
                position.x = x;
                position.y = y;
            }

            inline void setScale(const engine::Vec newScale) { scale = newScale; }

            inline void setScale(float x, float y, float z) {
                scale.x = x;
                scale.y = y;
                scale.z = z;
            }

            inline void setScale(float x, float y) {
                scale.x = x;
                scale.y = y;
            }

            inline void setRotation(const engine::Vec newRotation) { rotationEuler = newRotation; }

            inline void setRotation(float x, float y, float z) {
                rotationEuler.x = x;
                rotationEuler.y = y;
                rotationEuler.z = z;
            }

            inline void setRotation(float x, float y) {
                rotationEuler.x = x;
                rotationEuler.y = y;
            }
    };
}