#pragma once

#include "shader.h"

namespace engine {

    // Simple abstraction of a shader and a texture with functionality to set any uniforms needed
    class Material {
        private:
            Shader sha;
            int tx = 0;
        public:
            Material(Shader &sha, int tex);
            Material& operator=(Material const&other) = default;
            void setUni(const char* name, const float* uniValue, int len);
            inline void setTexture(int tex) { tx = tex; }
            inline Shader &shader() { return sha; }
            [[nodiscard]] inline int texture() const { return tx; }
    };
}