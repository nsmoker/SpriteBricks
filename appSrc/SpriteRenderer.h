#pragma once

#include "game/game.h"
#include <entity/Entity.h>
#include <texture/Texture.h>
#include <math/vec.h>
#include <math/rectangle.h>
#include <external/json.hpp>

class SpriteRenderer : public engine::Component {
    private:
        void syncBoundsWithParentTrans(engine::Entity& entity);
    public:
        engine::Texture sprite;
        engine::Rectangle bounds;
        engine::Vec offset;
        engine::Vec scale;
        void init(engine::Entity& entity);
        void update(engine::Entity& entity);
        void atDraw(engine::Entity& entity);
        void drawEditor();

        void moveBounds(engine::Vec offset);
        void setBoundsSize(engine::Vec newSize);
        void setBoundsSize(float x, float y);

        const inline static std::string jObjectDecorator = "SpriteRenderer";

        nlohmann::json serialize();

        static void from_json(const nlohmann::json& j, SpriteRenderer& spriteRenderer);
};

void to_json(nlohmann::json& j, const SpriteRenderer& spriteRenderer);