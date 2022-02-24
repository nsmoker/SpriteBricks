#pragma once
#include <graphics/graphicsDevice.h>
#include <graphics/window.h>
#include <input/InputManager.h>

namespace engine {
    class Game 
    {
        public:
        GraphicsDevice* device;
        InputManager input;
        Game(int w, int h, const char* title);
        void run();
        virtual void init() {}
        virtual void update() {}
        virtual void draw() {}
        virtual void exit() {}
        ~Game();
        private:
        int width;
        int height;
        const char* title;
        Window window;
    };
}