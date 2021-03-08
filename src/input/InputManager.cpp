#include "InputManager.h"

namespace engine {
    InputManager::InputManager() {
        kbState = SDL_GetKeyboardState(&numKeys);
        oldState = new Uint8[numKeys];
        memcpy(oldState, kbState, numKeys * sizeof(Uint8));
        mouseState = SDL_GetMouseState(&mouseX, &mouseY);
        oldMouseState = mouseState;
    }

    void InputManager::update() {
        memcpy(oldState, kbState, numKeys * sizeof(Uint8));
        oldMouseState = mouseState;
        mouseState = SDL_GetMouseState(&mouseX, &mouseY);
        SDL_PumpEvents();
    }
    bool InputManager::keyDown(SDL_Keycode key) { return kbState[key]; }
    bool InputManager::keyPressed(SDL_Keycode key) { return kbState[key] && !oldState[key]; }
    bool InputManager::keyReleased(SDL_Keycode key) { return !kbState[key] && oldState[key]; }
    bool InputManager::keyHeld(SDL_Keycode key) { return kbState[key] && oldState[key]; }
    Vec InputManager::mousePos() { return Vec((float) mouseX, (float) mouseY); }
    bool InputManager::mouseDown(MouseButton mb) { return mouseState & SDL_BUTTON(mb); }
    bool InputManager::mousePressed(MouseButton mb) { return (mouseState & SDL_BUTTON(mb)) && !(oldMouseState & SDL_BUTTON(mb)); }
    bool InputManager::mouseReleased(MouseButton mb) { return !(mouseState & SDL_BUTTON(mb)) && (oldMouseState & SDL_BUTTON(mb)); }
    bool InputManager::mouseHeld(MouseButton mb) { return (mouseState & SDL_BUTTON(mb)) && (oldMouseState & SDL_BUTTON(mb)); }
    InputManager::~InputManager() {
        delete[] oldState;
    }
}