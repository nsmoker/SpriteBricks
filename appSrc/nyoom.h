#pragma once

#include "editor/Editor.h"
#include "entity/Transform.h"
#include "external/dear_imgui/imgui.h"
#include "external/json.hpp"
#include <entity/Component.h>
#include <entity/Entity.h>
#include <string>

class Nyoom : public engine::Component {
    private:
    engine::Vec velocity;
    public:
    void init(engine::Entity& entity) {}
    void update(engine::Entity& entity) {
        entity.getComponent<engine::Transform>()->position += velocity;
    }
    void atDraw(engine::Entity& entity) {}

    inline void drawEditor() {
        ImGui::Text("Nyoom");
        ImGui::Text("Velocity");
        engine::drawVecEditor(velocity);
    }

    const static inline std::string jObjectDecorator = "Nyoom";
    nlohmann::json serialize() { return nlohmann::json{{"decorator", jObjectDecorator}}; };
    static void from_json(const nlohmann::json &j, Nyoom &nyoom) { }
};