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
            unsigned int id;
            int width;
            int height;
            int numChannels;
            GraphicsDevice* _device;

            void loadImage(std::string filePath);
       public:
            TextureFiltering textureFiltering = Nearest;
            std::string path;
            Rectangle srcRect;

            Texture();
            Texture(std::string filePath);
            Texture(std::string filePath, GraphicsDevice *device);
            Texture(std::string filePath, Rectangle sRect);
            Texture(std::string filePath, Rectangle sRect, GraphicsDevice *device);
            void loadFromPath(std::string filePath);
            explicit Texture(const Texture* that);
            Texture& operator=(const Texture* that);
            inline void upload(GraphicsDevice *device) {
                 id = device->uploadTexture(imageData.get(), width, height, numChannels);
                 device->setTextureFiltering(id, textureFiltering);
                 _device = device;
            }
            Texture subTex(Rectangle sRect);
            [[nodiscard]] inline unsigned int getId() const { return id; }
            void unload();
            ~Texture();

            inline unsigned int getWidth() { return surf->w * srcRect.w; }
            inline unsigned int getHeight() { return surf->h * srcRect.h; }
    };

    using json = nlohmann::json;
    void to_json(json& j, const Texture& texture);
    void from_json(const json& j, Texture& texture);
}