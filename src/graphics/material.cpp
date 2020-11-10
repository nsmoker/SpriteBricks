#include "material.h"
#include <cstring>
#include <iostream>

namespace engine {
    Material::Material(Shader* shader, int tex) {
        sha = shader;
        tx = tex;
    }

    void Material::setUni(const char* name, const float* vals, int len) {
        std::vector<UniformInfo>* unis = sha->getUniforms();
        for(int i = 0; i < unis->size(); ++i) {
            UniformInfo& uni = unis->at(i);
            if(strcmp(uni.name, name) == 0) {
                for(int j = 0; j < len; ++j) {
                    uni.value.push_back(vals[j]);
                }
            }
        }
    }
}