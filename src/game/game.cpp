#include "game.h"
#include "../graphics/window.h"
#include "../graphics/graphicsDevice.h"
#include "../graphics/batcher.h"
#include <external/dear_imgui/imgui.h>
#include <external/dear_imgui/imgui_impl_sdl.h>
#include <external/dear_imgui/imgui_impl_opengl3.h>

namespace engine {

    void Game::setWindowSize(int w, int h) {
        width = w;
        height = h;
    }

    void Game::addEntity(Entity *entity) {
        entity->setId(entities.size());
        entities.push_back(entity);
    }

    Entity* Game::getEntityOfId(int id) {
        if (entities.size() <= id) {
            SDL_Log("Warning: no entity of id %i present.", id);
            return nullptr;
        }

        Entity* entity = entities[id];
        if (entity->getId() != id) {
            SDL_Log("Warning: no entity of id %i present.", id);
            return nullptr;
        }

        return entity;
    }

    void Game::clearEntities() {
        for (auto p : entities) {
            delete p;
        }
        entities.clear();
    }

    void Game::run() {
        window.init(width, height, title);
        device.init(window.getContext());
        batcher = new Batcher(&device);

        init();

        SDL_Event event;
        bool done = false;
        while(!done) {
            while(SDL_PollEvent(&event) != 0) {
                ImGui_ImplSDL2_ProcessEvent(&event);
                if(event.type == SDL_QUIT) {
                    done = true;
                    break;
                } else if(event.type == SDL_CONTROLLERDEVICEADDED) {
                    int32_t i = event.cdevice.which;
                    input.addController(i);
                } else if(event.type == SDL_CONTROLLERDEVICEREMOVED) {
                    int32_t i = event.cdevice.which;
                    input.removeController(i);
                }
            }
            update();
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplSDL2_NewFrame();
            ImGui::NewFrame();
            draw();
            input.update();
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            window.swap();
        }

        exit();
        delete batcher;
        window.quit();
    }

    Game::~Game() {
        for (auto p : entities) {
            delete p;
        }

        delete batcher;
        delete title;
    }
}