#include "batcher.h"
#include "math/vec.h"
#include <algorithm>
#include <iostream>

namespace engine {
    const char* vertexSource = R"glsl(
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
            gl_Position = vec4(vec2(position.x * cos(rotation) - position.y * sin(rotation), position.y * cos(rotation) + position.x * sin(rotation)) * scale + origin, 0, 1.0);
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

    Batcher::Batcher() : shader(vertexSource, fragSource), material(shader, 0) {
        mesh = _device->createMesh();
        mesh.vertSize = 11 * sizeof(float);
    }

    Batcher::Batcher(GraphicsDevice *device) : shader(vertexSource, fragSource), material(shader, 0), _device(device) {
        if (!shader.hasLinked() || !shader.hasCompiled()) {
            char linkageLog[1024];
            shader.getShaderProgramLog(linkageLog, 1024);
            char vertLog[1024];
            char fragLog[1024];
            shader.getShaderCompilationLog(vertLog, fragLog, 1024, 1024);

            SDL_Log("Shader program with id %i failed to link or compile. \n Linkage Log: %s \n Compilation Log for Vertex Shader: %s \n Compilation Log for Fragment Shader: %s", shader.id(), linkageLog, vertLog, fragLog);
        }
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

    Vec Batcher::transVec(const Vec& vecToTransform) const {
        Vec screenSize = _device->getViewportSize();
        Vec halfScale = screenSize / 2.0f;
        Vec ret = Vec((vecToTransform.x - halfScale.x) / halfScale.x + 1, (halfScale.y - vecToTransform.y) / halfScale.y - 1);
        return ret;
    }

    Rectangle Batcher::transRect(const Rectangle &other) const {
        Vec screenSize = _device->getViewportSize();
        float halfWidth = screenSize.x / 2.0f;
        float halfHeight = screenSize.y / 2.0f;
        float retW = other.w / halfWidth;
        float retH = other.h / halfHeight;
        float retX = (other.x - halfWidth) / halfWidth;
        float retY = (halfHeight - other.y) / halfHeight;
        return Rectangle(retW, retH, retX, retY);
    }


    Batcher& Batcher::operator=(Batcher const&other) {
        origin = other.origin;
        verts = other.verts;
        elems = other.elems;
        shader = other.shader;
        material = engine::Material(shader, 0);
        mesh = other.mesh;
        return *this;
    }

    void Batcher::draw(Texture& tex, Rectangle destRect, float scaleX, float scaleY, float rotation, float a, float r,
                       float g, float b) {
        Rectangle srcRect = tex.srcRect;
        Rectangle dest = useScreenDimensions ? transRect(destRect) : destRect;
        if(tex.getId() == -1) tex.upload(_device);
        elems.push_back(verts.size());
        elems.push_back(verts.size() + 1);
        elems.push_back(verts.size() + 2);
        elems.push_back(verts.size() + 1);
        elems.push_back(verts.size() + 2);
        elems.push_back(verts.size() + 3);
        verts.push_back(Vertex {
            dest.x,
            dest.y,
            srcRect.top_left().x,
            srcRect.bottom_right().y,
            scaleX, scaleY, r, g, b, a, rotation, tex.getId()});  // Bottom left
        verts.push_back(Vertex {
            dest.x,
            dest.y + (useScreenDimensions ? -dest.h : dest.h),
            srcRect.top_left().x,
            srcRect.top_left().y,
            scaleX, scaleY, r, g, b, a, rotation, (unsigned int) tex.getId()}); // Top left
        verts.push_back(Vertex {
            dest.x + dest.w,
            dest.y,
            srcRect.bottom_right().x,
            srcRect.bottom_right().y,
            scaleX, scaleY, r, g, b, a, rotation, (unsigned int) tex.getId()}); // Top right
        verts.push_back(Vertex {
            dest.x + dest.w,
            dest.y + (useScreenDimensions ? -dest.h : dest.h),
            srcRect.bottom_right().x,
            srcRect.top_left().y,
            scaleX, scaleY, r, g, b, a, rotation, (unsigned int) tex.getId()}); // Bottom right
    }

    void Batcher::render() {
        // Sort the vector by texture
        std::sort(verts.begin(), verts.end(), [](Vertex v, Vertex v2) { return v.tex < v2.tex; });

        // Evil pointer arithmetic to get the vertex data without the TextureInfo
        std::vector<float> actualData(verts.size() * 11);
        for(int i = 0; i < verts.size() * 11; i += 11) {
            auto evilPointer = (float*) &verts[i / 11];
            for(int j = 0; j < 11; ++j) {
                actualData[i + j] = evilPointer[j];
            }
        }
        Vec transformedOrigin = transVec(origin);
        float ori[] = { transformedOrigin.x, transformedOrigin.y };
        SDL_Log("Origin: x: %f, y: %f", transformedOrigin.x, transformedOrigin.y);
        material.setUni("origin", ori, 2);
        int tex = -1;
        int offset = 0;
        for(int i = 0; i < verts.size(); ++i) {
            if(tex != -1 && verts[i].tex != tex || i == verts.size() - 1) {
                material.setTexture(tex);
                _device->meshVertexData(mesh, &actualData[offset * 11], (i + 1) - offset);
                _device->meshElementData(mesh, elems.data(), elems.size());
                _device->render(RenderInfo { mesh, material });
                tex = verts[i].tex;
                offset = i;
            } else {
                tex = verts[i].tex;
            }
        }
        verts.clear();
        elems.clear();
    }
};