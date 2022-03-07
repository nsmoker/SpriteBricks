#pragma once
#define MAX_CONTROLLERS 8
#define CTRLR_BTNS 15
#define AXIS_MAX 32767

#include "SDL.h"
#include <vector>
#include <map>
#include <iostream>
#include <set>
#include "../math/vec.h"

namespace engine {
    enum MouseButton { LeftMB = 1, MiddleMB, RightMB, MB4, MB5, MB6, MB7, MB8};
    enum ControllerButton { ButtonA, ButtonB, ButtonX, ButtonY, ButtonBack, ButtonGuide, ButtonStart,
            ButtonLStick, ButtonRStick, ButtonLShoulder, ButtonRShoulder, ButtonDPUp,
            ButtonDPDown, ButtonDPLeft, ButtonDPRight};
    enum ControllerAxis { LeftX, LeftY, RightX, RightY, TriggerLeft, TriggerRight };

    class InputManager {
        private:
            int numKeys;
            uint8_t* oldState;
            const uint8_t* kbState;
            uint32_t oldMouseState;
            uint32_t mouseState;
            int mouseX;
            int mouseY;
            int numControllers = 0;
            bool oldControllers[MAX_CONTROLLERS * CTRLR_BTNS];
            bool useOldState = false;
            SDL_GameController* controllers[MAX_CONTROLLERS];
        public:
            float ctrlrDeadzone = 0.2f;
            InputManager();
            void update();
            void removeController(int32_t jsi);
            Vec mousePos() const;
            bool addController(int32_t jsi);
            bool ctrlrDown(int ctrlrIdx, ControllerButton btn);
            bool ctrlrHeld(int ctrlrIdx, ControllerButton btn);
            bool ctrlrReleased(int ctrlrIdx, ControllerButton btn);
            bool ctrlrPressed(int ctrlrIdx, ControllerButton btn);
            float ctrlrAxis(ControllerAxis axis, int32_t ctrlrIdx);
            bool mousePressed(MouseButton mb) const;
            bool mouseReleased(MouseButton mb) const;
            bool mouseDown(MouseButton mb) const;
            bool mouseHeld(MouseButton mb);
            bool keyPressed(SDL_Keycode key);
            bool keyDown(SDL_Keycode key);
            bool keyReleased(SDL_Keycode key);
            bool keyHeld(SDL_Keycode key);
            ~InputManager();
    };
}