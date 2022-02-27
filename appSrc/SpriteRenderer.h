#pragma once

#include <entity/Entity.h>
#include <texture/Texture.h>
#include <math/vec.h>
#include <math/rectangle.h>

class SpriteRenderer : public engine::Component {
    private:
        engine::Texture* tex;
        engine::Rectangle bounds;
        engine::Vec offset;

        void syncBoundsWithParentTrans(engine::Entity& entity);

    public:
        void init(engine::Entity& entity);
        void update(engine::Entity& entity);
        void atDraw(engine::Entity& entity);

        inline void setSprite(engine::Texture& texture) { tex = &texture; }
        void moveBounds(engine::Vec offset);
        void setBoundsSize(engine::Vec newSize);
        void setBoundsSize(float x, float y);
};