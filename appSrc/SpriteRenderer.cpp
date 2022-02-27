#include "SpriteRenderer.h"
#include <entity/Transform.h>
#include "TestGame.h"

void SpriteRenderer::syncBoundsWithParentTrans(engine::Entity& entity) {
    engine::Transform* trans = entity.getComponent<engine::Transform>();
    engine::Vec position = trans->getPosition() + offset;
    engine::Vec scale = trans->getScale();
    bounds.setX(position.x);
    bounds.setY(position.y);
    bounds.setWidth(scale.x);
    bounds.setHeight(scale.y);
}

void SpriteRenderer::init(engine::Entity& entity) {
    syncBoundsWithParentTrans(entity);
}

void SpriteRenderer::update(engine::Entity& entity) {
    syncBoundsWithParentTrans(entity);
}

void SpriteRenderer::atDraw(engine::Entity& entity) {
    engine::Game::instance<TestGame>().batcher->draw(*tex, bounds);
}

void SpriteRenderer::moveBounds(engine::Vec offset) {
    bounds.setX(bounds.posX() + offset.x);
    bounds.setY(bounds.posY() + offset.y);
}

void SpriteRenderer::setBoundsSize(engine::Vec newSize) {
    bounds.setHeight(newSize.y);
    bounds.setWidth(newSize.x);
}

void SpriteRenderer::setBoundsSize(float x, float y) {
    bounds.setHeight(y);
    bounds.setWidth(x);
}