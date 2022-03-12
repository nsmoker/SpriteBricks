#include "SpriteRenderer.h"
#include <entity/Transform.h>
#include <external/json.hpp>
#include "TestGame.h"
#include "editor/Editor.h"
#include "external/dear_imgui/imgui.h"
#include "game/game.h"

void to_json(nlohmann::json& j, const SpriteRenderer& spriteRenderer) {
    j = nlohmann::json{{"sprite", spriteRenderer.sprite}, {"bounds", spriteRenderer.bounds}, {"offset", spriteRenderer.offset}, {"scale", spriteRenderer.scale}};
    j["decorator"] = SpriteRenderer::jObjectDecorator;
}

void SpriteRenderer::from_json(const nlohmann::json &j, SpriteRenderer &spriteRenderer) {
    j.at("sprite").get_to(spriteRenderer.sprite);
    spriteRenderer.sprite.upload(&engine::Game::instance<TestGame>().device);
    j.at("bounds").get_to(spriteRenderer.bounds);
    j.at("offset").get_to(spriteRenderer.offset);
    j.at("scale").get_to(spriteRenderer.scale);
}

void SpriteRenderer::syncBoundsWithParentTrans(engine::Entity& entity) {
    engine::Transform* trans = entity.getComponent<engine::Transform>();
    engine::Vec position = trans->position + offset;
    bounds.x = position.x;
    bounds.y = position.y;
}

void SpriteRenderer::init(engine::Entity& entity) {
    syncBoundsWithParentTrans(entity);
}

void SpriteRenderer::update(engine::Entity& entity) {
    syncBoundsWithParentTrans(entity);
    bounds.w = scale.x;
    bounds.h = scale.y;
}

void SpriteRenderer::atDraw(engine::Entity& entity) {
    engine::Game::instance<TestGame>().batcher->draw(sprite, bounds, 1., 1., 0, 1, color.x, color.y, color.z);
}

void SpriteRenderer::moveBounds(engine::Vec offset) {
    bounds.x = bounds.x + offset.x;
    bounds.y = bounds.y + offset.y;
}

void SpriteRenderer::setBoundsSize(engine::Vec newSize) {
    bounds.h = newSize.y;
    bounds.w = newSize.x;
}

void SpriteRenderer::setBoundsSize(float x, float y) {
    bounds.h = y;
    bounds.w = x;
}

void SpriteRenderer::drawEditor() {
    ImGui::Text("Sprite Renderer");
    ImGui::Separator();
    ImGui::Text("Sprite");
    ImGui::Image((ImTextureID) (size_t) sprite.getId(), ImVec2(128, 128),
                 ImVec2(sprite.srcRect.top_left().x, sprite.srcRect.bottom_right().y),
                 ImVec2(sprite.srcRect.bottom_right().x, sprite.srcRect.top_left().y),
                 ImVec4(1,1,1,1), ImVec4(0.5, 0.5, 1.0, 0.5));
    ImGui::Separator();
    ImGui::Text("Source Rectangle");
    engine::drawRectangleEditor(sprite.srcRect);
    ImGui::Separator();
    ImGui::Text("Offset");
    engine::drawVecEditor(offset);
    ImGui::Separator();
    ImGui::Text("Scale");
    engine::drawVecEditor(scale);
}

nlohmann::json SpriteRenderer::serialize() {
    nlohmann::json j;
    to_json(j, *this);
    j["decorator"] = jObjectDecorator;
    return j;
}