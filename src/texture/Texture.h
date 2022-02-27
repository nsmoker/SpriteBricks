#pragma once
#include "../math/rectangle.h"
#include "../graphics/graphicsDevice.h"
#include "SDL_log.h"
#include <memory>
#include <string>

namespace engine {
    class Texture {
       private:
            std::shared_ptr<unsigned char> imageData;
            int id;
            int width;
            int height;
            int numChannels;
            GraphicsDevice* _device;

            void loadImage(const char* filePath);
       public:
            Rectangle srcRect;
            std::string path;

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
            ~Texture();
    };

    using json = nlohmann::json;
    void to_json(json& j, const Texture& texture);
    void from_json(const json& j, Texture& texture);
}