#include "external/dear_imgui/imgui.h"
#include <editor/Editor.h>

namespace engine {
    void drawRectangleEditor(Rectangle& rect) {
        ImGui::PushID(&rect);
        ImGui::InputFloat("x", &rect.x);
        ImGui::InputFloat("y", &rect.y);
        ImGui::InputFloat("h", &rect.h);
        ImGui::InputFloat("w", &rect.w);
        ImGui::PopID();
    }

    void drawVecEditor(Vec &vec) {
        ImGui::PushID(&vec);
        ImGui::InputFloat("x", &vec.x);
        ImGui::InputFloat("y", &vec.y);
        ImGui::InputFloat("z", &vec.z);
        ImGui::PopID();
    }
}