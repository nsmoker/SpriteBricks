#include "graphicsDevice.h"
#include <SDL2/SDL_image.h>
#include <iostream>
#include <stdint.h>

namespace engine {

    void GLAPIENTRY gl_message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
        std::cout << "OpenGL: " << message << std::endl;
    }

    void GraphicsDevice::init(SDL_GLContext context) {
        ctx = context;
        active = true;
        glewExperimental = GL_TRUE;
        glewInit();
        glEnable(GL_DEBUG_OUTPUT);
	    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(gl_message_callback, nullptr);
    }

    void GraphicsDevice::clear(int r, int g, int b, int a) const {
        if(active) {
            glClearColor(r, g, b, a);
            glClear(GL_COLOR_BUFFER_BIT);
        } 
    }

    MeshInfo GraphicsDevice::createMesh() {
        auto ret = MeshInfo { 0, 0, 0, 0, 0, 0, 0 };
        glGenVertexArrays(1, &ret.vertArrayID);
        return ret;
    }

    // TODO: This being here is actually evil. It should move into an image layer.
    TextureInfo GraphicsDevice::createTextureFromFile(const char* path) {
        auto ret = TextureInfo { 0 };
        glGenTextures(1, &ret.id);
        glBindTexture(GL_TEXTURE_2D, ret.id);
        SDL_Surface* surf = IMG_Load(path);
        GLint mode = surf->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, mode, surf->w, surf->h, 0, mode, GL_UNSIGNED_BYTE, surf->pixels);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
        SDL_FreeSurface(surf);
        return ret;
    }

    void GraphicsDevice::meshVertexData(MeshInfo &mesh, float data[], GLuint count) {
        glBindVertexArray(mesh.vertArrayID);
        if(mesh.vertBufferID == 0) glGenBuffers(1, &mesh.vertBufferID);
        glBindBuffer(GL_ARRAY_BUFFER, mesh.vertBufferID);
        glBufferData(GL_ARRAY_BUFFER, count * mesh.vertSize, data, GL_DYNAMIC_DRAW);
        glBindVertexArray(0);
    }

    void GraphicsDevice::meshElementData(MeshInfo &mesh, GLuint data[], GLuint count) {
        mesh.numElements = count;
        glBindVertexArray(mesh.vertArrayID);
        if(mesh.elemBufferID == 0) glGenBuffers(1, &mesh.elemBufferID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.elemBufferID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * count, data, GL_DYNAMIC_DRAW);
        glBindVertexArray(0);
    }

    void GraphicsDevice::meshInstanceData(MeshInfo mesh, float data[], GLuint count) {
        glBindVertexArray(mesh.vertArrayID);
        if(mesh.instBufferID == 0) glGenBuffers(1, &mesh.instBufferID);
        mesh.numInstances = count;
        glBindBuffer(GL_ARRAY_BUFFER, mesh.instBufferID);
        glBufferData(GL_ARRAY_BUFFER, mesh.instanceSize * count, data, GL_DYNAMIC_DRAW);
        glBindVertexArray(0);
    }

    void GraphicsDevice::enableAttributes(MeshInfo &mesh, VertexAttributeInfo attribs[], GLuint vertSize, GLuint numAttribs) {
        glBindVertexArray(mesh.vertArrayID);
        if(mesh.vertBufferID == 0) glGenBuffers(1, &mesh.vertBufferID);
        glBindBuffer(GL_ARRAY_BUFFER, mesh.vertBufferID);
        ulong compsInBytes = 0;
        for(int i = 0; i < numAttribs; ++i) {
            VertexAttributeInfo vert = attribs[i];
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, vert.numComponents, GL_FLOAT, vert.normalized, mesh.vertSize, (void * ) compsInBytes);
            compsInBytes += vert.numComponents * sizeof(float);
        }
        glBindVertexArray(0);
    }

    void GraphicsDevice::setTextureWrapping(TextureInfo tex, GLint type) {
        glBindTexture(GL_TEXTURE_2D, tex.id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, type);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, type);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void GraphicsDevice::setTextureFiltering(TextureInfo tex, GLint type) {
        glBindTexture(GL_TEXTURE_2D, tex.id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, type);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, type);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void GraphicsDevice::render(RenderInfo call) {
        glUseProgram(call.material.shader()->id());
        for(int i = 0; i < call.material.shader()->getNumUniforms(); ++i) {
            UniformInfo uni = call.material.shader()-> getUniform(i);
            switch (uni.tp) {
                case GL_FLOAT_VEC2:
                    glUniform2fv(uni.loc, uni.arraySize, uni.value.data());
                    break;
                case GL_FLOAT_VEC3:
                    glUniform3fv(uni.loc, uni.arraySize, uni.value.data());
                    break;
                default:
                    break;
            }
        }
        glBindVertexArray(call.mesh.vertArrayID);
        glBindBuffer(GL_ARRAY_BUFFER, call.mesh.vertBufferID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, call.mesh.elemBufferID);
        glBindTexture(GL_TEXTURE_2D, call.material.texture());
        glDrawElements(GL_TRIANGLES, call.mesh.numElements, GL_UNSIGNED_INT, (void *) (std::intptr_t) call.mesh.firstElem);
        glBindVertexArray(0);
    }
}