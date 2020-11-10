#include "shader.h"

namespace engine {
    Shader::Shader(const char vertexSource[], const char fragmentSource[]) {
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(vertexShader, 1, &vertexSource, nullptr);
        glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);

        glCompileShader(vertexShader);
        glCompileShader(fragmentShader);

        programID = glCreateProgram();
        glAttachShader(programID, vertexShader);
        glAttachShader(programID, fragmentShader);

        glLinkProgram(programID);

        // Get the attributes
        GLint numAttribs; 
        glGetProgramiv(programID, GL_ACTIVE_ATTRIBUTES, &numAttribs);
        for(int i = 0; i < numAttribs; ++i) {
            ShaderAttributeInfo inf;
            glGetActiveAttrib(programID, i, SHADER_NAME_MAX, nullptr, &inf.arraySize, &inf.tp, inf.name);
            inf.loc = i;
            attributes.push_back(inf);
        }

        // Get the uniforms
        GLint numUnis;
        glGetProgramiv(programID, GL_ACTIVE_UNIFORMS, &numUnis);
        for(int i = 0; i < numUnis; ++i) {
            UniformInfo inf;
            glGetActiveUniform(programID, i, SHADER_NAME_MAX, nullptr, &inf.arraySize, &inf.tp, inf.name);
            inf.loc = i;
            uniforms.push_back(inf);
        }
    }
}