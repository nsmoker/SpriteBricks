#include "InputManager.h"

namespace engine {
    InputManager::InputManager() {
        kbState = SDL_GetKeyboardState(&numKeys);
        oldState = new Uint8[numKeys];
        memcpy(oldState, kbState, numKeys * sizeof(Uint8));
    }

    void InputManager::update() {
        memcpy(oldState, kbState, numKeys * sizeof(Uint8));
        SDL_PumpEvents();
    }
    bool InputManager::keyDown(SDL_Keycode key) { return kbState[key] == 1; }
    bool InputManager::keyPressed(SDL_Keycode key) { return kbState[key] == 1 && oldState[key] == 0; }
    InputManager::~InputManager() {
        delete[] oldState;
    }
}