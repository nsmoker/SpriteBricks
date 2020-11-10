#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <map>
#include <iostream>

namespace engine {
    class InputManager {
        private:
            int numKeys;
            Uint8* oldState;
            const Uint8* kbState;
        public:
            InputManager();
            void update();
            bool keyPressed(SDL_Keycode key);
            bool keyDown(SDL_Keycode key);
            ~InputManager();
    };
}