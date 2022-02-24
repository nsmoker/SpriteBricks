#include "game.h"
#include "../graphics/window.h"
#include "../graphics/graphicsDevice.h"
#include "../graphics/batcher.h"

namespace engine {

    Game::Game(int w, int h, const char* t): input()
    {
        width = w;
        height = h;
        title = t;
        window.init(width, height, title);
        window.createContext();

        device = new GraphicsDevice();
        device->init(window.getContext());
    }

    void Game::run()
    {
        init();

        SDL_Event event;
        bool done = false;
        while(!done) 
        {
            while(SDL_PollEvent(&event) != 0)
            {
                if(event.type == SDL_QUIT) {
                    done = true;
                    break;
                } else if(event.type == SDL_CONTROLLERDEVICEADDED) {
                    int32_t i = event.cdevice.which;
                    input.addController(i);
                } else if(event.type == SDL_CONTROLLERDEVICEREMOVED) {
                    int32_t i = event.cdevice.which;
                    input.removeController(i);
                }
            }
            update();
            draw();
            input.update();
            window.swap();
        }

        exit();
        window.quit();
    }

    Game::~Game() {
        delete device;
    }
}