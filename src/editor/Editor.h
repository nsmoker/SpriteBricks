#pragma once
#include "SDL_log.h"
#include <external/dear_imgui/imgui.h>
#include <external/json.hpp>
#include <string>
#include <map>
#include <functional>
#include <entity/Entity.h>
#include <entity/Component.h>
#include <game/game.h>
#include <fstream>
#include <entity/Transform.h>

namespace engine {

    template <class T>
    void addComponentOfType(Entity& entity, nlohmann::json& j) {
        T& comp = entity.addComponent<T>();
        T::from_json(j, comp);
    }

    template <class T>
    class Editor {
        private:
            Editor() { registerDecorator(Transform::jObjectDecorator, &addComponentOfType<Transform>); }
            std::map<std::string, std::function<void(Entity&, nlohmann::json&)>> decoratorFactoryMap;
        public:
            inline const static std::string sceneDecorator = "Scene";
            inline const static std::string entityArrayDecorator = "Entities";

            static Editor& getInstance() {
                static Editor<T>* editor = new Editor<T>();
                return *editor;
            };
            inline void registerDecorator(std::string key, const std::function<void(Entity&, nlohmann::json&)> factory) {
                decoratorFactoryMap.emplace(key, factory);
            }
            void loadFromScene(std::string fileName);
            void saveScene(std::string fileName);
            void init();
            void update();
            void draw();
    };

    template <class T>
    void Editor<T>::saveScene(std::string fileName) {
        Game& game = Game::instance<T>();
        nlohmann::json json;
        nlohmann::json jsonArray = nlohmann::json::array();
        json["decorator"] = "Scene";
        for (Entity* entity : game.entities) {
            nlohmann::json entityJson;
            to_json(entityJson, *entity);
            jsonArray.push_back(entityJson);
        }
        json[entityArrayDecorator] = jsonArray;

        std::ofstream stream(fileName);
        stream << json.dump(4);
        stream.close();
    }

    template <class T>
    void Editor<T>::loadFromScene(std::string filename) {
        std::ifstream stream(filename);
        nlohmann::json j = json::parse(stream);
        nlohmann::json entityArray = j[entityArrayDecorator];
        if (entityArray.is_null() || j["decorator"].get<std::string>() != sceneDecorator) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "No entity array found in scene file.");
        }

        Game::instance<T>().clearEntities();

        for (nlohmann::json& entityJObject : entityArray) {
            if (entityJObject[Entity::componentArrayDecorator].is_null() || entityJObject["decorator"].get<std::string>() != Entity::jObjectDecorator) {
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Scene file corrupt: invalid entity.");
                return;
            }

            Entity* entity = new Entity();
            nlohmann::json componentArray = entityJObject[Entity::componentArrayDecorator];
            for (auto& componentJObject : componentArray) {
                std::string decorator = componentJObject["decorator"].get<std::string>();
                if (decoratorFactoryMap.count(decorator) == 0) {
                    SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Ignoring component with unregistered decorator type %s.", decorator.c_str());
                    continue;
                }

                auto factory = decoratorFactoryMap[decorator];
                factory(*entity, componentJObject);
            }

            Game::instance<T>().addEntity(entity);
        }
    }
}