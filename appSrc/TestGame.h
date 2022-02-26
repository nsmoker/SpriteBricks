#ifndef ENGINE_TESTGAME_H
#define ENGINE_TESTGAME_H

#include <game/game.h>
#include <texture/Texture.h>
#include <graphics/batcher.h>
#include <math/rectangle.h>
#include <math/vec.h>

class TestGame : public engine::Game {
private:
    engine::Texture spriteSheet;
    engine::Texture tex;
    engine::Texture otherTex;
    engine::Vec playerPos = engine::Vec(400, 400);
public:
    using engine::Game::Game;

    void init() override {
        spriteSheet = engine::Texture("sprites.png", &device);
        tex = spriteSheet.subTex(engine::Rectangle(1 / 16.0f, 1 / 16.0f, 8.0f / 16.0f, 0));
        otherTex = spriteSheet.subTex(engine::Rectangle(1 / 16.0f, 1 / 16.0f, 1 / 16.0f, 0));
        device.setTextureFiltering(tex.getId(), GL_NEAREST);
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
        engine::Rectangle playerRectangle(128, 128, playerPos.x, playerPos.y);
        engine::Rectangle opponentRectangle(128, 128, 600, 600);
        device.clear(0, 0, 0, 1);
        batcher.draw(tex, playerRectangle);
        batcher.draw(otherTex, opponentRectangle);
        batcher.render();
    }
};


#endif //ENGINE_TESTGAME_H