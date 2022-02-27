#include "Entity.h"
#include <typeinfo>
#include "Transform.h"

namespace engine {
    Entity::Entity(): id(-1) {
        addComponent<Transform>();
    }

    Entity::~Entity() {
        for (int i = 0; i < components.size(); ++i) {
            delete components[i];
        }
    }
}