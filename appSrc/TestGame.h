#ifndef ENGINE_TESTGAME_H
#define ENGINE_TESTGAME_H

#include <game/game.h>
#include <texture/Texture.h>
#include <graphics/batcher.h>
#include <math/rectangle.h>
#include <math/vec.h>
#include "SDL.h"

class TestGame : public engine::Game {
private:
    engine::Texture tex;
    engine::Batcher batcher;
    engine::Vec playerPos = engine::Vec(400, 400);
public:
    using engine::Game::Game;

    void init() override {
        tex = engine::Texture("sprites.png", device);
        device->setTextureFiltering(tex.getId(), GL_NEAREST);
        batcher = engine::Batcher(device);
    }

    void update() override {
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
        // if(input.ctrlrDown(0, engine::ButtonA)) {
        //     engine::Vec lStick = engine::Vec(input.ctrlrAxis(engine::LeftX, 0), input.ctrlrAxis(engine::LeftY, 0));
        //     playerPos.x += 5.0f * lStick.x;
        //     playerPos.y += 5.0f * lStick.y;
        // }
        // if(input.ctrlrPressed(0, engine::ButtonLStick)) {
        //     playerPos.x = 400.0f;
        //     playerPos.y = 400.0f;
        // }
    }

    void draw() override {
        engine::Rectangle rectangle(128, 128, playerPos.x, playerPos.y);
        glViewport(0, 0, 1280, 720);
        device->clear(0, 0, 0, 1);
        batcher.draw(tex, rectangle);
        batcher.render();
    }
};


#endif //ENGINE_TESTGAME_H