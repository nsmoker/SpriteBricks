#include "Texture.h"
#include "SDL_log.h"
#include <stdexcept>
#include "../external/json.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <external/stb_image.h>

namespace engine {
    using json = nlohmann::json;

    void to_json(json &j, const Texture& texture) {
        j = json{{"srcRect", texture.srcRect}, {"path", texture.path}};
    }

    void from_json(const json &j, Texture& texture) {
        j.at("srcRect").get_to(texture.srcRect);
        std::string path = j.at("path");
        if (!path.empty()) {
            texture.loadFromPath(path);
        }
    }

    void Texture::loadFromPath(std::string filePath) {
        path = filePath;
        imageData.reset(stbi_load(filePath.c_str(), &width, &height, &numChannels, 0));
        unload();
        id = -1;
    }

    void Texture::loadImage(std::string filePath) {
        imageData.reset(stbi_load(filePath.c_str(), &width, &height, &numChannels, 0));
        if (!imageData.get()) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "stbi couldn't load image: %s", stbi_failure_reason());
            std::runtime_error("Invalid texture!");
        }
    }

    Texture::Texture(): srcRect(1, 1, 0, 0), width(1), height(1), numChannels(4) {
        id = -1;
        imageData.reset(new unsigned char[16]);
        for (int i = 0; i < 16; ++i) {
            imageData.get()[i] = 255;
        }
    }

    Texture::Texture(const Texture* that): srcRect(that->srcRect) {
        imageData = that->imageData;
        id = that->getId();
    }

    Texture& Texture::operator=(const Texture *that) {
        srcRect = that->srcRect;
        imageData = that->imageData;
        id = that->getId();
        return *this;
    }

    Texture::Texture(std::string filePath): srcRect(1, 1, 0, 0), id(-1) {
        loadImage(filePath);
    }

    Texture::Texture(std::string filePath, GraphicsDevice *device): srcRect(1, 1, 0, 0) {
        loadImage(filePath);
        upload(device);
    }

    Texture::Texture(std::string filePath, Rectangle sRect): srcRect(sRect), id(-1) {
        loadImage(filePath);
    }

    Texture::Texture(std::string filePath, Rectangle sRect, GraphicsDevice *device): srcRect(sRect) {
        loadImage(filePath);
        upload(device);
    }

    Texture Texture::subTex(Rectangle sRect) {
        Texture ret(this);
        ret.path = path;
        ret.srcRect = sRect;
        return ret;
    }

    void Texture::unload()  {
        _device->deleteTexture(id);
        _device = nullptr;
    }

    Texture::~Texture() {
        _device->deleteTexture(id);
    }
}