#pragma once

#include <entity/Component.h>
#include <entity/Entity.h>

class PlayerController : public engine::Component {
    void init(engine::Entity& entity) {}
    void update(engine::Entity& entity);
    void atDraw(engine::Entity& entity) {}
};