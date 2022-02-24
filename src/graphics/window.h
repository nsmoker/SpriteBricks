#pragma once

#include "SDL.h"
#include "SDL_opengl.h"

namespace engine {
    // Wrapper around SDL's windowing functions
    class Window {
        private:
            // Pointer to the underlying window struct
            SDL_Window* window;
            // Width and height of the window
            int w, h;
            // Struct for event handling
            SDL_Event event;
            SDL_GLContext ctx;
        public:
            // Initialize SDL's event handling and create a window with size width by height called title
            void init(int width, int height, const char title[]);
            // Instruct SDL to capture the mouse;
            void captureMouse();
            // Create an OpenGL context with reasonable attributes and sets it as the current context
            void createContext();
            // Get a reference to the context
            inline SDL_GLContext getContext() { return ctx; }
            // Enable vSync
            void vSync();
            // Swap the window
            void swap();
            // Delay t milliseconds
            void sleep(int t);
            // Quit; destroy the window and OpenGL context
            void quit();
    };

}