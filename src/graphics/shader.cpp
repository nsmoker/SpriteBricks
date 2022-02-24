#include "shader.h"

namespace engine {
    bool Shader::hasLinked() const {
        GLint linkageStatus;
        glGetProgramiv(programID, GL_LINK_STATUS, &linkageStatus);
        return linkageStatus == GL_TRUE;
    }

    bool Shader::hasCompiled() const {
        GLint compileStatusVertex;
        GLint compileStatusFrag;
        glGetShaderiv(vertexID, GL_COMPILE_STATUS, &compileStatusVertex);
        glGetShaderiv(fragID, GL_COMPILE_STATUS, &compileStatusFrag);
        return compileStatusVertex == GL_TRUE && compileStatusFrag == GL_TRUE;
    }

    void Shader::getShaderProgramLog(char* destination, int size) const {
        GLsizei logLength = 0;
        glGetProgramInfoLog(programID, size, &logLength, destination);
    }

    void Shader::getShaderCompilationLog(char* vertexShaderDest, char* fragmentShaderDest, int size1, int size2) const {
        GLsizei logLength = 0;
        glGetShaderInfoLog(vertexID, size1, &logLength, vertexShaderDest);
        glGetShaderInfoLog(fragID, size2, &logLength, fragmentShaderDest);
    }

    void Shader::linkProgram(GLuint vertexID, GLuint fragID) {
        programID = glCreateProgram();
        glAttachShader(programID, vertexID);
        glAttachShader(programID, fragID);

        glLinkProgram(programID);

        GLint linkageStatus;
        glGetProgramiv(programID, GL_LINK_STATUS, &linkageStatus);
    }

    GLuint Shader::compileSource(const char* source, bool isVertex) {
        GLuint shaderID = glCreateShader(isVertex ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
        glShaderSource(shaderID, 1, &source, nullptr);
        glCompileShader(shaderID);
        return shaderID;
    }

    Shader::Shader(const char vertexSource[], const char fragmentSource[]) {
        vertexID = compileSource(vertexSource, true);
        fragID = compileSource(fragmentSource, false);

        linkProgram(vertexID, fragID);

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