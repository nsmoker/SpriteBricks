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
        for (int i = 0; i < entities.size(); ++i) {
            entities[i]->update();
        }
    }

    void draw() override {
        SpriteRenderer* playerRenderer = player->getComponent<SpriteRenderer>();
        engine::Transform* transform = player->getComponent<engine::Transform>();
        float playerColumn = playerRenderer->sprite.srcRect.x * 16.0f;
        float playerRow = playerRenderer->sprite.srcRect.y * 16.0f;
        std::string path = playerRenderer->sprite.path;
        std::string scenePath = "scene.json";
        scenePath.resize(512);
        static bool done = false;
        static char buf[50];
        if (!done) {
            for (int i = 0; i < 50; ++i) buf[i] = '\0';
            path.copy(buf, path.size(), 0);
        }
        done = true;

        ImGui::Begin("Player texture editor");
        ImGui::InputFloat("Column", &playerColumn);
        ImGui::InputFloat("Row", &playerRow);
        ImGui::InputFloat("Player x", &transform->position.x);
        ImGui::InputFloat("Player y", &transform->position.y);
        ImGui::InputText("Path", buf, IM_ARRAYSIZE(buf));
        if (ImGui::Button("Load from path")) {
            playerRenderer->sprite = engine::Texture(buf, &device);
        }

        ImGui::InputText("Scene path", scenePath.data(), 512 * sizeof(char));

        if (ImGui::Button("Save scene")) {
            editor.saveScene(scenePath);
        }

        if (ImGui::Button("Load scene")) {
            editor.loadFromScene(scenePath);
        }

        playerRenderer->sprite.srcRect.x = playerColumn / 16.0f;
        playerRenderer->sprite.srcRect.y = playerRow / 16.0f;

        ImGui::End();

        //ImGui::ShowDemoWindow();

        engine::Rectangle opponentRectangle(128, 128, 600, 600);
        device.clear(0, 0, 0, 1);

        for (int i = 0; i < entities.size(); ++i) {
            entities[i]->atDraw();
        }
        batcher->render();
    }
};