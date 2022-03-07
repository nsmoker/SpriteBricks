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
    engine::Texture spriteSheet;
    engine::Texture playerTex;
    engine::Texture otherTex;
    engine::Entity player;
    engine::Editor<TestGame> editor = engine::Editor<TestGame>::getInstance();
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
        player.addComponent<SpriteRenderer>()->sprite = playerTex;
        player.addComponent<PlayerController>();
        auto playerTrans = player.getComponent<engine::Transform>();
        playerTrans->setPosition(400, 400);
        playerTrans->setScale(200, 200);
        addEntity(player);
        nlohmann::json js;
        to_json(js, player);
    }

    void update() override {
        for (int i = 0; i < entities.size(); ++i) {
            entities[i].update();
        }
    }

    void draw() override {
        SpriteRenderer* playerRenderer = player.getComponent<SpriteRenderer>();
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
        ImGui::InputText("Path", buf, IM_ARRAYSIZE(buf));
        if (ImGui::Button("Load from path")) {
            playerRenderer->sprite = engine::Texture(buf, &device);
        }

        ImGui::InputText("Scene path", scenePath.data(), 512 * sizeof(char));

        if (ImGui::Button("Save scene")) {
            editor.saveScene(scenePath);
        }

        playerRenderer->sprite.srcRect.x = playerColumn / 16.0f;
        playerRenderer->sprite.srcRect.y = playerRow / 16.0f;

        ImGui::End();

        //ImGui::ShowDemoWindow();

        engine::Rectangle opponentRectangle(128, 128, 600, 600);
        device.clear(0, 0, 0, 1);

        for (int i = 0; i < entities.size(); ++i) {
            entities[i].atDraw();
        }
        batcher->render();
    }
};