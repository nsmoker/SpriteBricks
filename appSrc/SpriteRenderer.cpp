#include "SpriteRenderer.h"
#include <entity/Transform.h>
#include <external/json.hpp>
#include "TestGame.h"
#include "game/game.h"

void to_json(nlohmann::json& j, const SpriteRenderer& spriteRenderer) {
    j = nlohmann::json{{"sprite", spriteRenderer.sprite}, {"bounds", spriteRenderer.bounds}, {"offset", spriteRenderer.offset}};
    j["decorator"] = SpriteRenderer::jObjectDecorator;
}

void SpriteRenderer::from_json(const nlohmann::json &j, SpriteRenderer &spriteRenderer) {
    j.at("sprite").get_to(spriteRenderer.sprite);
    spriteRenderer.sprite.upload(&engine::Game::instance<TestGame>().device);
    j.at("bounds").get_to(spriteRenderer.bounds);
    j.at("offset").get_to(spriteRenderer.offset);
}

void SpriteRenderer::syncBoundsWithParentTrans(engine::Entity& entity) {
    engine::Transform* trans = entity.getComponent<engine::Transform>();
    engine::Vec position = trans->position + offset;
    bounds.x = position.x;
    bounds.y = position.y;
    bounds.w = trans->scale.x;
    bounds.h = trans->scale.y;
}

void SpriteRenderer::init(engine::Entity& entity) {
    syncBoundsWithParentTrans(entity);
}

void SpriteRenderer::update(engine::Entity& entity) {
}

void SpriteRenderer::atDraw(engine::Entity& entity) {
    syncBoundsWithParentTrans(entity);
    engine::Game::instance<TestGame>().batcher->draw(sprite, bounds);
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

nlohmann::json SpriteRenderer::serialize() {
    nlohmann::json j;
    to_json(j, *this);
    j["decorator"] = jObjectDecorator;
    return j;
}