#pragma once

#include "shader.h"

namespace engine {

    // Simple abstraction of a shader and a texture with functionality to set any uniforms needed
    class Material {
        private:
            Shader* sha;
            int tx;
        public:
            Material(Shader* shade, int tex);
            void setUni(const char* name, const float* uniValue, int len);
            inline void setTexture(int tex) { tx = tex; }
            inline Shader* shader() { return sha; }
            inline int texture() { return tx; }
    };
}