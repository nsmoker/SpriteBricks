#pragma once
#include <external/dear_imgui/imgui.h>
#include <external/json.hpp>
#include <string>
#include <map>
#include <functional>
#include <entity/Entity.h>
#include <entity/Component.h>
#include <fstream>

namespace engine {

    template <class T>
    class Editor {
        private:
            Editor() {}
            std::map<std::string, std::function<void(Entity&)>> decoratorFactoryMap;
        public:
            static Editor& getInstance() {
                static Editor<T>* editor = new Editor<T>();
                return *editor;
            };
            void loadFromScene(std::string fileName);
            void saveScene(std::string fileName);
            void init();
            void update();
            void draw();
    };

    template <class T>
    void addComponentOfType(Entity& entity) {
        entity.addComponent<T>();
    }

    template <class T>
    void Editor<T>::saveScene(std::string fileName) {
        Game& game = Game::instance<T>();
        nlohmann::json json;
        nlohmann::json jsonArray = nlohmann::json::array();
        json["decorator"] = "Scene";
        for (Entity& entity : game.entities) {
            nlohmann::json entityJson;
            to_json(entityJson, entity);
            jsonArray.push_back(entityJson);
        }
        json["components"] = jsonArray;

        std::ofstream stream(fileName);
        stream << jsonArray;
        stream.close();
    }

    template <class T>
    void Editor<T>::loadFromScene(std::string filename) {
        std::ifstream stream(filename);
        nlohmann::json j = json::parse(stream);
    }
}