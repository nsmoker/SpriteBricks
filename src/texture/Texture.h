#pragma once
#include "../math/rectangle.h"
#include "SDL_image.h"
#include "../graphics/graphicsDevice.h"

namespace engine {
    class Texture {
       private:
            SDL_Surface* surf;
            Rectangle srcRect;
            uint id;
       public:
            Texture(const char* filePath, GraphicsDevice device);
            Texture(const char* filePath, Rectangle sRect, GraphicsDevice device);
            explicit Texture(const Texture* that);
            inline void setSrcRect(Rectangle srcRectP) { srcRect = srcRectP; }
            inline void upload(GraphicsDevice device) { id = device.uploadTexture(surf->pixels, surf->w, surf->h, surf->format->BytesPerPixel); }
            Texture subTex(Rectangle sRect);
            inline void setId(int nid) { id = nid; }
            [[nodiscard]] inline uint getId() const { return id; }
            inline Rectangle getSrcRect() { return srcRect; }
            ~Texture();
    };
}