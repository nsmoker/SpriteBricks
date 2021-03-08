#include "Texture.h"

namespace engine {

    Texture::Texture(): srcRect(1, 1, 0, 0) {
        id = -1;
    }

    Texture::Texture(SDL_Surface *surface) : srcRect(1, 1, 0, 0) {
        surf = surface;
        id = -1;
    }

    Texture::Texture(const Texture* that): srcRect(that->srcRect) {
        surf = that->surf;
        surf->refcount++;
        id = that->getId();
    }

    Texture& Texture::operator=(const Texture *that) {
        setSrcRect(that->srcRect);
        surf = that->surf;
        surf->refcount++;
        id = that->getId();
        return *this;
    }

    Texture::Texture(const char *filePath): srcRect(1, 1, 0, 0) {
        std::atexit(IMG_Quit);
        surf = IMG_Load(filePath);
        id = -1;
    }

    Texture::Texture(const char* filePath, GraphicsDevice &device): srcRect(1, 1, 0, 0) {
        std::atexit(IMG_Quit);
        surf = IMG_Load(filePath);
        upload(device);
    }

    Texture::Texture(const char *filePath, Rectangle sRect): srcRect(sRect) {
        std::atexit(IMG_Quit);
        surf = IMG_Load(filePath);
        id = -1;
    }

    Texture::Texture(const char *filePath, Rectangle sRect, GraphicsDevice &device): srcRect(sRect) {
        std::atexit(IMG_Quit);
        surf = IMG_Load(filePath);
        upload(device);
    }

    Texture Texture::subTex(Rectangle sRect) {
        Texture ret(this);
        ret.setSrcRect(sRect);
        return ret;
    }

    Texture::~Texture() {
        if(surf->refcount == 1) {
            SDL_FreeSurface(surf);
        } else {
            surf->refcount--;
        }
    }
}