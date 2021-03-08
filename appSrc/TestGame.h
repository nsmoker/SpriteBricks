#ifndef ENGINE_TESTGAME_H
#define ENGINE_TESTGAME_H

#include <game/game.h>
#include <texture/Texture.h>
#include <graphics/batcher.h>
#include <math/rectangle.h>
#include <math/vec.h>
#include <SDL2/SDL.h>

class TestGame : public engine::Game {
private:
    engine::Texture tex;
    engine::Batcher batcher;
    Vec playerPos = Vec(400, 400);
public:
    using engine::Game::Game;

    void init() override {
        tex = engine::Texture("/home/nick/Programming/BasicEngine/appSrc/res/sprites.png", device);
        device.setTextureFiltering(tex.getId(), GL_NEAREST);
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
    }

    void draw() override {
        engine::Rectangle rectangle(600, 400, playerPos.x, playerPos.y);
        device.clear(0, 0, 0, 1);
        batcher.draw(tex, rectangle);
        batcher.render();
    }
};


#endif //ENGINE_TESTGAME_H