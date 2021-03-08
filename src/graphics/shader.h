#pragma once
#define SHADER_NAME_MAX 255

#include <vector>
#include "GL/glew.h"
#include "GL/gl.h"

namespace engine {
    // Data type that provides information about a shader attribute
    struct ShaderAttributeInfo {
        GLuint loc;
        GLint arraySize;
        GLenum tp;
        char name[SHADER_NAME_MAX];
    };
    // Data type that provides information about a uniform
    struct UniformInfo {
        // Type of the uniform
        GLenum tp;
        // Name of the uniform
        char name[SHADER_NAME_MAX];
        GLint arraySize;
        GLuint loc;
        std::vector<float> value;
    };

    class Shader {
        private:
            GLuint programID{};
            std::vector<ShaderAttributeInfo> attributes;
            std::vector<UniformInfo> uniforms;
        public:
            Shader(const char vertexSource[], const char fragmentSource[]);
            inline std::vector<ShaderAttributeInfo> getAttributes() { return attributes; }
            inline std::vector<UniformInfo>& getUniforms() { return uniforms; }
            inline UniformInfo getUniform(int i) { return uniforms[i]; }
            inline int getNumUniforms() { return uniforms.size(); }
            [[nodiscard]] inline GLuint id() const { return programID; }
    };
}