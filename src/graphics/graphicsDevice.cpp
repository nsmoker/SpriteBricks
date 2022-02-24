#include "graphicsDevice.h"
#include <iostream>
#include <cstdint>
#include "../math/vec.h"

namespace engine {

    void GLAPIENTRY gl_message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
        //SDL_Log("OpenGL: %s \n", message);
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
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        } 
    }

    MeshInfo GraphicsDevice::createMesh() {
        auto ret = MeshInfo { 0, 0, 0, 0, 0, 0, 0 };
        glGenVertexArrays(1, &ret.vertArrayID);
        return ret;
    }

    int GraphicsDevice::uploadTexture(void* data, int width, int height, int bytesPerPixel) {
        unsigned int id;
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);
        GLint mode = bytesPerPixel == 4 ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, mode, width, height, 0, mode, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
        return id;
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
        unsigned long compsInBytes = 0;
        for(int i = 0; i < numAttribs; ++i) {
            VertexAttributeInfo vert = attribs[i];
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, vert.numComponents, GL_FLOAT, vert.normalized, mesh.vertSize, (void * ) (std::intptr_t) compsInBytes);
            compsInBytes += vert.numComponents * sizeof(float);
        }
        glBindVertexArray(0);
    }

    void GraphicsDevice::setTextureWrapping(int tex, GLint type) {
        glBindTexture(GL_TEXTURE_2D, tex);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, type);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, type);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void GraphicsDevice::setTextureFiltering(int tex, GLint type) {
        glBindTexture(GL_TEXTURE_2D, tex);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, type);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, type);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    Vec GraphicsDevice::getViewportSize() {
        int net[4];
        glGetIntegerv(GL_VIEWPORT, net);
        return Vec((float) net[2], (float) net[3]);
    }

    void GraphicsDevice::render(RenderInfo call) {
        glUseProgram(call.material.shader().id());
        for(int i = 0; i < call.material.shader().getNumUniforms(); ++i) {
            UniformInfo uni = call.material.shader().getUniform(i);
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