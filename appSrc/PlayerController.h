#pragma once

#include <entity/Component.h>
#include <entity/Entity.h>
#include <string>

class PlayerController : public engine::Component {
    void init(engine::Entity& entity) {}
    void update(engine::Entity& entity);
    void atDraw(engine::Entity& entity) {}
    std::string serialize();
};