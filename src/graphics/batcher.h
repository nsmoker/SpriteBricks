#pragma once

#include "graphicsDevice.h"
#include "../math/rectangle.h"
#include "../texture/Texture.h"
#include "math/vec.h"

namespace engine {
    /*
     * A sprite batcher. Efficiently renders 2D textures and can handle rotations and scaling. This is the low level class.
     */
    class Batcher {
        private:
            // This is an internal struct that should never be touched by anything outside the batcher. 
            struct Vertex {
                float posX;
                float posY;
                float texCoordX;
                float texCoordY;
                float scaleX;
                float scaleY;
                float r;
                float g;
                float b;
                float a;
                float rotation;
                unsigned int tex;
            };
            GraphicsDevice *_device;
            std::vector<Vertex> verts;
            std::vector<GLuint> elems;
            Shader shader;
            Material material;
            MeshInfo mesh;
            Vec transVec(const Vec& toTrans) const;
            Rectangle transRect(const Rectangle& other) const;
        public:
            Vec origin;
            bool useScreenDimensions = true;
            Batcher();
            explicit Batcher(GraphicsDevice *device);
            Batcher& operator=(Batcher const&other);
            // Submit a texture for drawing. Note that this just adds it to the queue, you need to call render to actually make things appear.
            void draw(Texture& tex, Rectangle dest, float scaleX = 1.0f, float scaleY = 1.0f, float rotation = 0, float a = 1.0f,
                      float r = 1.0f, float g = 1.0f, float b = 1.0f);
            // This draws everything in the queue and then clears it. You should probably call this every frame if you're using the batcher.
            void render();
    };
}