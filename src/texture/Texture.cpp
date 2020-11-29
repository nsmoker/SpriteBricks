#include "Texture.h"

namespace engine {

    Texture::Texture(const Texture* that) : srcRect(that->srcRect) {
        std::atexit(IMG_Quit);
        surf = that->surf;
        surf->refcount++;
        id = that->getId();
    }

    Texture::Texture(const char *filePath, GraphicsDevice device): srcRect(1, 1, 0, 0) {
        surf = IMG_Load(filePath);
        id = device.uploadTexture(surf->pixels, surf->w, surf->h, surf->format->BytesPerPixel);
    }

    Texture::Texture(const char *filePath, Rectangle sRect, GraphicsDevice device): srcRect(sRect) {
        surf = IMG_Load(filePath);
        id = device.uploadTexture(surf->pixels, surf->w, surf->h, surf->format->BytesPerPixel);
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