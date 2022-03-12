#pragma once

#include <filesystem>
#include <game/game.h>
#include <texture/Texture.h>
#include <graphics/batcher.h>
#include <math/rectangle.h>
#include <math/vec.h>
#include <entity/Entity.h>
#include "SpriteRenderer.h"
#include "PlayerController.h"
#include <entity/Transform.h>

class TestGame : public engine::Game {
private:
    engine::Texture spriteSheet;
    engine::Texture playerTex;
    engine::Texture otherTex;
    engine::Entity player;
public:
    using engine::Game::Game;

    void init() override {
        for (int i = 0; i < entities.size(); ++i) {
            entities[i].init();
        }
        spriteSheet = engine::Texture((std::filesystem::current_path() / "appSrc/res/sprites.png").c_str(), &device);
        playerTex = spriteSheet.subTex(engine::Rectangle(1 / 16.0f, 1 / 16.0f, 8.0f / 16.0f, 0));
        otherTex = spriteSheet.subTex(engine::Rectangle(1 / 16.0f, 1 / 16.0f, 1 / 16.0f, 0));
        device.setTextureFiltering(playerTex.getId(), GL_NEAREST);
        player.addComponent<SpriteRenderer>()->setSprite(playerTex);
        player.addComponent<PlayerController>();
        auto playerTrans = player.getComponent<engine::Transform>();
        playerTrans->setPosition(400, 400);
        playerTrans->setScale(200, 200);
        addEntity(player);
    }

    void update() override {
        for (int i = 0; i < entities.size(); ++i) {
            entities[i].update();
        }
    }

    void draw() override {
        engine::Rectangle opponentRectangle(128, 128, 600, 600);
        device.clear(0, 0, 0, 1);
        for (int i = 0; i < entities.size(); ++i) {
            entities[i].atDraw();
        }
        batcher->render();
    }
};