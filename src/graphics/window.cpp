#include "window.h"
#include <iostream>

namespace engine {
    void Window::init(int width, int height, const char title[]) {
        SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_JOYSTICK);
        SDL_JoystickEventState(SDL_ENABLE);
        w = width;
        h = height;
        // Tell SDL we want a reasonably modern context
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        // Make SDL play nice with modern window managers
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
        // Let vsync happen
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);


        window = SDL_CreateWindow(title, 100, 100, w, h, SDL_WINDOW_OPENGL);
    }

    void Window::captureMouse() { SDL_CaptureMouse(SDL_TRUE); }

    void Window::createContext() {
        ctx = SDL_GL_CreateContext(window);
        SDL_GL_MakeCurrent(window, ctx);
    }

    void Window::vSync() { SDL_GL_SetSwapInterval(1); }

    void Window::swap() { 
        SDL_GL_SwapWindow(window); 
    }

    void Window::sleep(int t) { SDL_Delay(t); }

    void Window::quit() {
        SDL_DestroyWindow(window);
        SDL_GL_DeleteContext(ctx);
        SDL_Quit();
    }
}