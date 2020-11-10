#include <graphics/batcher.h>
#include <graphics/window.h>
#include <input/InputManager.h>
#define _USE_MATH_DEFINES
#include <cmath>

using namespace engine;

int main() {
    Window wind;
    wind.init(1280, 720, "test");
    wind.createContext();
    engine::GraphicsDevice device;
    device.init(wind.getContext());

    Batcher batcher(device);
    InputManager input;
    float posX = -0.5f;
    float posY = -0.5f;
    TextureInfo myTex = device.createTextureFromFile("../../appSrc/res/sprites.png");
    device.setTextureFiltering(myTex, GL_NEAREST);

    SDL_Event event;
    bool done = false;
    while(!done) {
        input.update();
        while(SDL_PollEvent(&event) != 0) {
            if(event.type == SDL_QUIT) {
                done = true;
                break;
            }
        }
        Rectangle rectangle(1, 1, posX, posY);
        if(input.keyDown(SDL_SCANCODE_D)) posX += 0.01f;
        if(input.keyDown(SDL_SCANCODE_A)) posX -= 0.01f;

        device.clear(0, 0, 0, 1);
        batcher.draw(myTex, rectangle, 1.0f, 1.0f, 0, 1.0f, 1.0f, 1.0f, 1.0f, 8.0f / 16.0f, 0, 9.0f / 16.0f,1.0f / 16.0f);
        batcher.render();

        wind.swap();
    }

    wind.quit();
}