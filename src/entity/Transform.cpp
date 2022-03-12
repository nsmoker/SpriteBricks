#include "Transform.h"
#include "editor/Editor.h"
#include "external/dear_imgui/imgui.h"

namespace engine {

    void to_json(nlohmann::json& j, const Transform& transform) {
        j = nlohmann::json{{"position", transform.position}, {"scale", transform.scale}, {"rotation", transform.rotationEuler}};
        j["decorator"] = Transform::jObjectDecorator;
    }

    nlohmann::json Transform::serialize() {
        auto j = nlohmann::json();
        j["decorator"] = jObjectDecorator;
        to_json(j, *this);
        return j;
     }

     void Transform::drawEditor() {
         ImGui::Text("Transform");
         ImGui::Separator();
         ImGui::Text("Position");
         drawVecEditor(position);
         ImGui::Text("Rotation");
         drawVecEditor(rotationEuler);
         ImGui::Text("Scale");
         drawVecEditor(scale);
     }
}