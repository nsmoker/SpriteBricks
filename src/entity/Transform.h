#pragma once

#include <entity/Component.h>
#include <math/vec.h>
#include <external/json.hpp>

namespace engine {
    class Transform : public Component {
        public:
            inline const static std::string jObjectDecorator = "Transform";

            void init(Entity& entity) {}
            void update(Entity& entity) {}
            void atDraw(Entity& entity) {}
            
            engine::Vec position;
            engine::Vec scale;
            engine::Vec rotationEuler;

            inline void setPosition(float x, float y, float z) { 
                position.x = x;
                position.y = y;
                position.z = z;
            }
            
            inline void setPosition(float x, float y) {
                position.x = x;
                position.y = y;
            }

            inline void setScale(float x, float y, float z) {
                scale.x = x;
                scale.y = y;
                scale.z = z;
            }

            inline void setScale(float x, float y) {
                scale.x = x;
                scale.y = y;
            }

            inline void setRotation(float x, float y, float z) {
                rotationEuler.x = x;
                rotationEuler.y = y;
                rotationEuler.z = z;
            }

            inline void setRotation(float x, float y) {
                rotationEuler.x = x;
                rotationEuler.y = y;
            }

            nlohmann::json serialize();
            static void from_json(const nlohmann::json& j, Transform& transform) {
                j.at("position").get_to(transform.position);
                j.at("scale").get_to(transform.scale);
                j.at("rotation").get_to(transform.rotationEuler);
            }
    };

    void to_json(nlohmann::json& j, const Transform& transform);
}