#pragma once

#include "external/dear_imgui/imgui.h"
#include <entity/Component.h>
#include <entity/Entity.h>
#include <string>

class PlayerController : public engine::Component {
    public:
    void init(engine::Entity& entity) {}
    void update(engine::Entity& entity);
    void atDraw(engine::Entity& entity) {}

    inline void drawEditor() { ImGui::Text("PlayerController"); }

    const static inline std::string jObjectDecorator = "PlayerController";
    nlohmann::json serialize();
    static void from_json(const nlohmann::json &j, PlayerController &playerController) { }
};