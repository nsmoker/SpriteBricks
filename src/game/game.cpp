#include "game.h"
#include "../graphics/window.h"
#include "../graphics/graphicsDevice.h"
#include "../graphics/batcher.h"

namespace engine {

    Game::Game(int w, int h, const char* t)
    {
        width = w;
        height = h;
        title = t;
        window.init(width, height, title);
        window.createContext();

        GraphicsDevice device;
        device.init(window.getContext());
        this->device = device;
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
}