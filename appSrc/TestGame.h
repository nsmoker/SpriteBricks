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
#include <external/json.hpp>
#include <external/dear_imgui/imgui.h>
#include <external/dear_imgui/imgui_impl_sdl.h>
#include <external/dear_imgui/imgui_impl_opengl3.h>
#include <editor/Editor.h>

class TestGame : public engine::Game {
private:
    engine::Entity* player;
    engine::Editor<TestGame>& editor = engine::Editor<TestGame>::getInstance();
public:
    using engine::Game::Game;

    void addDecorators() {
        editor.registerDecorator(SpriteRenderer::jObjectDecorator, &engine::addComponentOfType<SpriteRenderer>);
        editor.registerDecorator(PlayerController::jObjectDecorator, &engine::addComponentOfType<PlayerController>);
    }

    void init() override {
        addDecorators();

        for (int i = 0; i < entities.size(); ++i) {
            entities[i]->init();
        }
        editor.loadFromScene((std::filesystem::current_path() / "appSrc/res/scene.json").c_str());

        player = getEntityOfId(0);
    }

    void update() override {
        editor.update();
        for (int i = 0; i < entities.size(); ++i) {
            entities[i]->update();
        }
    }

    void draw() override {
        editor.draw();

        device.clear(0, 0, 0, 1);

        for (int i = 0; i < entities.size(); ++i) {
            entities[i]->atDraw();
        }
        batcher->render();
    }
};