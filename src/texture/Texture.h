#pragma once
#include "../math/rectangle.h"
#include "../graphics/graphicsDevice.h"
#include "SDL_log.h"
#include <memory>

namespace engine {
    class Texture {
       private:
            std::shared_ptr<unsigned char> imageData;
            Rectangle srcRect;
            int id;
            int width;
            int height;
            int numChannels;
            GraphicsDevice* _device;

            void loadImage(const char* filePath);
       public:
            Texture();
            Texture(const char* filePath);
            Texture(const char* filePath, GraphicsDevice *device);
            Texture(const char* filePath, Rectangle sRect);
            Texture(const char *filePath, Rectangle sRect, GraphicsDevice *device);
            explicit Texture(const Texture* that);
            Texture& operator=(const Texture* that);
            inline void setSrcRect(Rectangle srcRectP) { srcRect = srcRectP; }
            inline void upload(GraphicsDevice *device) { id = device->uploadTexture(static_cast<void*>(imageData.get()), width, height, numChannels); }
            Texture subTex(Rectangle sRect);
            [[nodiscard]] inline unsigned int getId() const { return id; }
            inline Rectangle getSrcRect() const { return srcRect; }
            ~Texture();
    };
}