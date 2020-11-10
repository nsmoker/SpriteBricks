#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL.h>
#include "shader.h"
#include "material.h"

namespace engine {
    // Information about an OpenGL mesh.
    struct MeshInfo {
        // ID of the vertex array associated with the mesh
        GLuint vertArrayID;
        // ID of the vertex buffer associated with the mesh
        GLuint vertBufferID;
        // ID of the element buffer associated with the mesh
        GLuint elemBufferID;
        // ID of the instance buffer associated with the mesh
        GLuint instBufferID;
        // Size of the vertices used in the vertex buffer
        GLuint vertSize;
        // Number of instances
        GLuint numInstances;
        // Size of the instances
        GLuint instanceSize;
        // Number of elements to draw this mesh
        GLuint numElements;
        // First element index
        GLuint firstElem;
    };
    
    // Data type that provides information about an attribute of a vertex
    struct VertexAttributeInfo {
        // The number of components (floats) which comprise the attribute
        GLuint numComponents;
        // The index of the attribute's array
        GLuint loc;
        // Is the attribute normalized?
        bool normalized;
    };

    // Data type that encapsulates a texture
    struct TextureInfo {
        // The id of the OpenGL texture object.
        GLuint id;
    };

    // Data type that encapsulates a rendering call
    struct RenderInfo {
        MeshInfo mesh;
        Material material;
    };

    // Wrapper around an OpenGL device
    class GraphicsDevice {
        private:
            SDL_GLContext ctx;
        public:
            // Is the device ready to do something?
            bool active = false;

            // Initialize the device. Context has to be passed in to ensure we don't do anything crazy
            void init(SDL_GLContext ctx);

            // Clear the screen
            void clear(int r, int g, int b, int a) const;

            // Create an empty mesh 
            MeshInfo createMesh();

            TextureInfo createTextureFromFile(const char* path);

            // Create a shader
            inline engine::Shader createShader(const char* vertexSource, const char* fragmentSource) { return engine::Shader(vertexSource, fragmentSource); }

            // Assign data to a mesh's vertex buffers. If the buffers do not yet exist, generates them. 
            void meshVertexData(MeshInfo& mesh, float data[], GLuint count);

            // Assign data to a mesh's element array buffers. If the buffers do not yet exist, generates them.
            void meshElementData(MeshInfo &mesh, GLuint data[], GLuint count);

            // Assign data to mesh's instance buffers. If the buffers do not yet exist, generates them.
            void meshInstanceData(MeshInfo mesh, float data[], GLuint count);

            // Activate vertex attributes
            void enableAttributes(MeshInfo& mesh, VertexAttributeInfo attribs[], GLuint vertSize, GLuint numAttribs);

            // Sets the texture to use type for texture wrapping
            void setTextureWrapping(TextureInfo tex, GLint type);

            // Sets the texture to dest to use type for filtering
            void setTextureFiltering(TextureInfo tex, GLint filter);

            // Render stuff
            void render(RenderInfo call);

            // Kill the device
            void kill();
    };
}