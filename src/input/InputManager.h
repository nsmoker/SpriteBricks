#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <map>
#include <iostream>
#include "../math/vec.h"

namespace engine {
    enum MouseButton { LeftMB = 1, MiddleMB, RightMB, MB4, MB5, MB6, MB7, MB8};

    class InputManager {
        private:
            int numKeys;
            uint8_t* oldState;
            const uint8_t* kbState;
            uint32_t oldMouseState;
            uint32_t mouseState;
            int mouseX;
            int mouseY;
        public:
            InputManager();
            void update();
            Vec mousePos();
            bool mousePressed(MouseButton mb);
            bool mouseReleased(MouseButton mb);
            bool mouseDown(MouseButton mb);
            bool mouseHeld(MouseButton mb);
            bool keyPressed(SDL_Keycode key);
            bool keyDown(SDL_Keycode key);
            bool keyReleased(SDL_Keycode key);
            bool keyHeld(SDL_Keycode key);
            ~InputManager();
    };
}