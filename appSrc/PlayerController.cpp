#include "PlayerController.h"
#include <entity/Transform.h>
#include "TestGame.h"
#include <input/InputManager.h>

void PlayerController::update(engine::Entity& entity) {
    engine::Vec playerPos = entity.getComponent<engine::Transform>()->getPosition();
    engine::InputManager& input = engine::Game::instance<TestGame>().input;
    if(input.keyDown(SDL_SCANCODE_D)) {
        playerPos.x += 5;
    }
    if(input.keyDown(SDL_SCANCODE_A)) {
        playerPos.x -= 5;
    }
    if(input.keyPressed(SDL_SCANCODE_E)) {
        playerPos.x = 400;
        playerPos.y = 400;
    }
    if(input.mouseDown(engine::LeftMB)) {
        playerPos = input.mousePos();
    }

    entity.getComponent<engine::Transform>()->setPosition(playerPos);
}