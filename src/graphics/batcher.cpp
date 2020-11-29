#include "batcher.h"
#include <algorithm>
#include <iostream>

namespace engine {
    const char* vertexSource =
            R"glsl(
        #version 150 core

        in vec2 position;
        in vec2 texCoord;
        in vec2 scale;
        in vec4 col;
        in float rotation;

        out vec4 Color;
        out vec2 Tex;

        uniform vec2 origin;

        void main()
        {
            Color = col;
            Tex = texCoord;
            gl_Position = vec4(vec2(position.x * cos(rotation) - position.y * sin(rotation), position.y * cos(rotation) + position.x * sin(rotation)) * scale - origin, 0.0, 1.0);
        }
    )glsl";
    const char* fragSource = R"glsl(
        #version 150 core

        in vec2 Tex;
        in vec4 Color;

        out vec4 outColor;

        uniform sampler2D samp;

        void main()
        {
            outColor = texture(samp, Tex) * Color;
        }
    )glsl";

    Batcher::Batcher(GraphicsDevice &device) : shader(vertexSource, fragSource), material(&shader, 0) {
        _device = &device;
        verts = std::vector<Vertex>();
        mesh = _device->createMesh();
        mesh.vertSize = 11 * sizeof(float);
        VertexAttributeInfo atts[] = {
                VertexAttributeInfo { 2, 0, false},
                VertexAttributeInfo { 2, 2, false},
                VertexAttributeInfo { 2, 4, false},
                VertexAttributeInfo { 4, 6, false},
                VertexAttributeInfo {1, 11, false}
        };
        _device->enableAttributes(mesh, atts, 11, 5);
    }

    void Batcher::draw(Texture& tex, Rectangle dest, float scaleX, float scaleY, float rotation, float a, float r,
                       float g, float b) {
        Rectangle srcRect = tex.getSrcRect();
        elems.push_back(verts.size());
        elems.push_back(verts.size() + 1);
        elems.push_back(verts.size() + 2);
        elems.push_back(verts.size() + 1);
        elems.push_back(verts.size() + 2);
        elems.push_back(verts.size() + 3);
        verts.push_back(Vertex { dest.posX(), dest.posY(), srcRect.top_left().first, srcRect.top_left().second, scaleX, scaleY, r, g, b, a, rotation, tex.getId()}); // Top left
        verts.push_back(Vertex { dest.posX(), dest.posY() + dest.height(), srcRect.top_left().first, srcRect.bottom_right().second, scaleX, scaleY, r, g, b, a, rotation, tex.getId()}); // Bottom left
        verts.push_back(Vertex { dest.posX() + dest.width(), dest.posY(), srcRect.bottom_right().first, srcRect.top_left().second, scaleX, scaleY, r, g, b, a, rotation, tex.getId()}); // Top right
        verts.push_back(Vertex { dest.posX() + dest.width(), dest.posY() + dest.height(), srcRect.bottom_right().first, srcRect.bottom_right().second, scaleX, scaleY, r, g, b, a, rotation, tex.getId()}); // Bottom right
    }

    void Batcher::render() {
        // Sort the vector by texture
        std::sort(verts.begin(), verts.end(), [](Vertex v, Vertex v2) { return v.tex < v2.tex; });

        // Evil pointer arithmetic to get the vertex data without the TextureInfo
        float actualData[verts.size() * 11];
        for(int i = 0; i < verts.size() * 11; i += 11) {
            auto evilPointer = (float*) &verts[i / 11];
            for(int j = 0; j < 11; ++j) {
                actualData[i + j] = evilPointer[j];
            }
        }
        float ori[] = { xOrigin, yOrigin };
        material.setUni("origin", ori, 2);
        int tex = -1;
        int offset = 0;
        for(int i = 0; i < verts.size(); ++i) {
            if(tex != -1 && verts[i].tex != tex || i == verts.size() - 1) {
                material.setTexture(tex);
                _device->meshVertexData(mesh, &actualData[offset], (i + 1) - offset);
                _device->meshElementData(mesh, elems.data(), elems.size());
                _device->render(RenderInfo { mesh, material });
                tex = verts[i].tex;
                offset = i - 1;
            } else {
                tex = verts[i].tex;
            }
        }
        verts.clear();
        elems.clear();
    }
};