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
        j.at("path").get_to(texture.path);
    }

    void Texture::loadImage(const char* filePath) {
        imageData.reset(stbi_load(filePath, &width, &height, &numChannels, 0));
        if (!imageData.get()) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "stbi couldn't load image: %s", stbi_failure_reason());
            std::runtime_error("Invalid texture!");
        }
    }

    Texture::Texture(): srcRect(1, 1, 0, 0) {
        id = -1;
    }

    Texture::Texture(const Texture* that): srcRect(that->srcRect) {
        imageData = that->imageData;
        id = that->getId();
    }

    Texture& Texture::operator=(const Texture *that) {
        setSrcRect(that->srcRect);
        imageData = that->imageData;
        id = that->getId();
        return *this;
    }

    Texture::Texture(const char *filePath): srcRect(1, 1, 0, 0), id(-1) {
        loadImage(filePath);
    }

    Texture::Texture(const char* filePath, GraphicsDevice *device): srcRect(1, 1, 0, 0) {
        loadImage(filePath);
        upload(device);
    }

    Texture::Texture(const char *filePath, Rectangle sRect): srcRect(sRect), id(-1) {
        loadImage(filePath);
    }

    Texture::Texture(const char *filePath, Rectangle sRect, GraphicsDevice *device): srcRect(sRect) {
        loadImage(filePath);
        upload(device);
    }

    Texture Texture::subTex(Rectangle sRect) {
        Texture ret(this);
        ret.path = path;
        ret.srcRect = sRect;
        return ret;
    }

    Texture::~Texture() {
        _device->deleteTexture(id);
    }
}