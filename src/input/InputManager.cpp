#include "InputManager.h"
#include <cmath>
#include <external/dear_imgui/imgui.h>
#include <external/dear_imgui/imgui_impl_sdl.h>
#include <external/dear_imgui/imgui_impl_opengl3.h>

namespace engine {
    InputManager::InputManager() {
        kbState = SDL_GetKeyboardState(&numKeys);
        oldState = new Uint8[numKeys];
        memcpy(oldState, kbState, numKeys * sizeof(Uint8));
        mouseState = SDL_GetMouseState(&mouseX, &mouseY);
        oldMouseState = mouseState;
        for(int i = 0; numControllers < MAX_CONTROLLERS && i < SDL_NumJoysticks(); ++i) {
            if(!SDL_IsGameController(i)) {
                continue;
            } else {
                controllers[numControllers] = SDL_GameControllerOpen(i);
                ++numControllers;
                for(int j = 0; j < CTRLR_BTNS; ++j) {
                    oldControllers[CTRLR_BTNS * i + j] = SDL_GameControllerGetButton(controllers[i], (SDL_GameControllerButton) j);
                }
            }
        }
    }

    void InputManager::removeController(int32_t jsi) {
        SDL_GameController* ptr;
        SDL_GameControllerClose(controllers[jsi]);
    }

    void InputManager::update() {
        if(ImGui::GetIO().WantCaptureKeyboard) {
            useOldState = true;
        } else {
            useOldState = false;
            memcpy(oldState, kbState, numKeys * sizeof(Uint8));
        }
        for(int i = 0; i < MAX_CONTROLLERS; ++i) {
            if(SDL_IsGameController(i))  {
                for(int j = 0; j < CTRLR_BTNS; ++j) {
                    oldControllers[CTRLR_BTNS * i + j] = SDL_GameControllerGetButton(controllers[i], (SDL_GameControllerButton) j);
                }
            }
        }
        oldMouseState = mouseState;
        if (!ImGui::GetIO().WantCaptureMouse) mouseState = SDL_GetMouseState(&mouseX, &mouseY);
        SDL_PumpEvents();
    }
    bool InputManager::addController(int32_t jsi) {
        if(numControllers >= MAX_CONTROLLERS || jsi > MAX_CONTROLLERS - 1) {
            return false;
        } else {
            controllers[jsi] = SDL_GameControllerOpen(jsi);
            ++numControllers;
            return true;
        }
    }

    bool InputManager::ctrlrDown(int ctrlrIdx, ControllerButton btn) {
        return SDL_GameControllerGetButton(controllers[ctrlrIdx], (SDL_GameControllerButton) btn);
    }

    bool InputManager::ctrlrPressed(int ctrlrIdx, ControllerButton btn) {
        bool wasPressed = oldControllers[CTRLR_BTNS * ctrlrIdx + btn];
        return !wasPressed && ctrlrDown(ctrlrIdx, btn);
    }

    bool InputManager::ctrlrHeld(int ctrlrIdx, ControllerButton btn) {
        bool wasPressed = oldControllers[CTRLR_BTNS * ctrlrIdx + btn];
        return wasPressed && ctrlrDown(ctrlrIdx, btn);
    }

    bool InputManager::ctrlrReleased(int ctrlrIdx, ControllerButton btn) {
        bool wasPressed = oldControllers[CTRLR_BTNS * ctrlrIdx + btn];
        return wasPressed && !ctrlrDown(ctrlrIdx, btn);
    }

    float InputManager::ctrlrAxis(ControllerAxis axis, int32_t ctrlrIdx)
    {
        SDL_GameController* ctrlr = controllers[ctrlrIdx];
        int16_t ax = SDL_GameControllerGetAxis(ctrlr, (SDL_GameControllerAxis) axis);
        float ret_ax = (float) ax / (float) AXIS_MAX;
        return abs(ret_ax) < ctrlrDeadzone ? 0.0f : ret_ax;
    }
    bool InputManager::keyDown(SDL_Keycode key) { return useOldState ? oldState[key] : kbState[key]; }
    bool InputManager::keyPressed(SDL_Keycode key) { return kbState[key] && !oldState[key]; }
    bool InputManager::keyReleased(SDL_Keycode key) { return !kbState[key] && oldState[key]; }
    bool InputManager::keyHeld(SDL_Keycode key) { return kbState[key] && oldState[key]; }
    Vec InputManager::mousePos() const { return Vec((float) mouseX, (float) mouseY); }
    bool InputManager::mouseDown(MouseButton mb) const { return mouseState & SDL_BUTTON(mb); }
    bool InputManager::mousePressed(MouseButton mb) const { return (mouseState & SDL_BUTTON(mb)) && !(oldMouseState & SDL_BUTTON(mb)); }
    bool InputManager::mouseReleased(MouseButton mb) const { return !(mouseState & SDL_BUTTON(mb)) && (oldMouseState & SDL_BUTTON(mb)); }
    bool InputManager::mouseHeld(MouseButton mb) { return (mouseState & SDL_BUTTON(mb)) && (oldMouseState & SDL_BUTTON(mb)); }
    InputManager::~InputManager() {
        delete[] oldState;
    }
}