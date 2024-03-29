#pragma once
#include <graphics/graphicsDevice.h>
#include <graphics/window.h>
#include <input/InputManager.h>
#include <vector>
#include <entity/Entity.h>
#include <graphics/batcher.h>

namespace engine {
    class Game {
        public:
            GraphicsDevice device;
            InputManager input;
            Batcher* batcher;

            Game(Game const&) = delete;
            void operator=(Game const&) = delete;

            template <class T>
            static Game& instance();
            void setWindowSize(int w, int h);
            inline void setTitle(const char* newTitle) { title = newTitle; };

            void addEntity(Entity& entity);
            Entity* getEntityOfId(int id);

            void run();

            virtual void init() {}
            virtual void update() {}
            virtual void draw() {}
            virtual void exit() {}
        private:
            const char* title;
            Window window;
        protected:
            Game(): device(), input() {}
            std::vector<Entity> entities;
            int width;
            int height;
    };

    template <class T>
    Game& Game::instance() {
        static Game* current = new T();
        return *current;
    }
}