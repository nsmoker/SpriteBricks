#pragma once
#include "SDL_log.h"
#include "math/rectangle.h"
#include "math/vec.h"
#include <algorithm>
#include <cmath>
#include <external/dear_imgui/imgui.h>
#include <external/json.hpp>
#include <filesystem>
#include <iostream>
#include <optional>
#include <string>
#include <map>
#include <functional>
#include <entity/Entity.h>
#include <entity/Component.h>
#include <game/game.h>
#include <fstream>
#include <entity/Transform.h>
#include <vector>

namespace engine {
    void drawRectangleEditor(Rectangle& rect);

    void drawVecEditor(Vec& vec);

    template <class T>
    void addComponentOfType(Entity& entity, nlohmann::json& j) {
        T& comp = entity.addComponent<T>();
        if (!j.is_null()) {
            T::from_json(j, comp);
        }
    }

    template <class T>
    class Editor {
        private:
            Editor(): selectedEntity() { registerDecorator(Transform::jObjectDecorator, &addComponentOfType<Transform>); }
            std::map<std::string, std::function<void(Entity&, nlohmann::json&)>> decoratorFactoryMap;
            Entity* selectedEntity;
            char currentSceneFileNameBuffer[512];
            char entityNameBuffer[512];
            std::string currentSceneFileName;
            bool startedOnSelected = false;
            bool entityDragged = false;
            std::vector<Entity*> selectedEntities;
            std::vector<Entity*> boxedEntities;
            Vec lookPosition;

            void drawEntityEditor();
            void drawJsonObject(nlohmann::json& j);
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
    void Editor<T>::drawEntityEditor() {
        ImGui::Begin("Entity Inspector");

        if (selectedEntity) {
            if (ImGui::InputText("##entityName", entityNameBuffer, 512)) {
                selectedEntity->name.assign(entityNameBuffer);
            }
            for (auto component : selectedEntity->getComponents()) {
                component->drawEditor();
                ImGui::Separator();
            }
        }
        ImGui::End();
    }

    template <class T>
    void Editor<T>::update() { }

    template <class T>
    void Editor<T>::draw() {
        ImGuiWindowFlags baseFlags = ImGuiWindowFlags_NoBackground;
        baseFlags |= ImGuiWindowFlags_NoTitleBar;
        baseFlags |= ImGuiWindowFlags_NoMove;
        baseFlags |= ImGuiWindowFlags_NoResize;
        baseFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
        baseFlags |= ImGuiWindowFlags_NoScrollbar;
        baseFlags |= ImGuiWindowFlags_NoCollapse;

        Game& game = Game::instance<T>();
        game.batcher->origin = lookPosition;

        auto io = ImGui::GetIO();

        ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y));
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::Begin("base", nullptr, baseFlags);
        if (ImGui::InvisibleButton("baseButton", ImVec2(io.DisplaySize.x, io.DisplaySize.y))) {
            if (ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {
                Vec mousePosition = Vec(ImGui::GetMousePos()) + (Vec(0) - lookPosition);
                bool foundHit = false;
                for (Entity* entity : Game::instance<T>().entities) {
                    Transform* trans = entity->getComponent<Transform>();
                    if (trans->bounding.contains(mousePosition)) {
                        selectedEntity = entity;
                        foundHit = true;
                    }
                }
                if (!foundHit) {
                    selectedEntity = nullptr;
                }
                entityDragged = false;
            }
        }

        ImDrawList* drawList = ImGui::GetWindowDrawList();

        if (selectedEntity) {
            Rectangle entityBounds = selectedEntity->getComponent<Transform>()->bounding;
            drawList->AddRect(entityBounds.top_left() + lookPosition, entityBounds.bottom_right() + lookPosition,
                              ImGui::GetColorU32(IM_COL32(0, 0, 255, 255)));
        }

        ImGui::PushID("baseButton");

        boxedEntities.clear();
        if (ImGui::IsMouseDragging(ImGuiMouseButton_Left, 6) && ImGui::IsItemHovered()) {
            Vec clickPos = Vec(io.MouseClickedPos[0]) + (Vec(0) - lookPosition);
            if ((selectedEntity && selectedEntity->getComponent<Transform>()->bounding.contains(clickPos)) || entityDragged) {
                entityDragged = true;
                selectedEntity->getComponent<Transform>()->position += io.MouseDelta;
            } else {
                selectedEntity = nullptr;
                entityDragged = false;
                Vec topLeft = Vec(std::min(io.MousePos.x, io.MouseClickedPos[0].x), std::min(io.MouseClickedPos[0].y, io.MousePos.y)) + (Vec(0) - lookPosition);
                Rectangle rect(std::abs(io.MousePos.x - io.MouseClickedPos[0].x), std::abs(io.MousePos.y - io.MouseClickedPos[0].y), topLeft.x, topLeft.y);
                drawList->AddRectFilled(rect.top_left() + lookPosition, rect.bottom_right() + lookPosition, ImGui::GetColorU32(IM_COL32(20, 230, 20, 100)));
                for (Entity* entity : Game::instance<T>().entities) {
                    Transform* trans = entity->getComponent<Transform>();
                    if (rect.intersects(trans->bounding)) {
                        drawList->AddRect(trans->bounding.top_left() + lookPosition, trans->bounding.bottom_right() + lookPosition,
                                          ImGui::GetColorU32(IM_COL32(255, 255, 255, 255)));
                        boxedEntities.push_back(entity);
                    }
                }
            }
        }

        if (ImGui::IsMouseDragging(ImGuiMouseButton_Middle, 6) && ImGui::IsItemHovered()) {
            lookPosition += io.MouseDelta;
        }

        ImGui::PopID();

        ImGui::End();

        const char* sceneInputId = "Scene path input";
        bool openSceneInputPopup = false;
        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Save scene")) {
                    if (currentSceneFileName.empty()) {
                        openSceneInputPopup = true;
                    } else {
                        saveScene(currentSceneFileName);
                    }
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Edit")) {
                if (ImGui::MenuItem("Add Entity")) {
                    Entity* toAdd = new Entity("Entity" + std::to_string(game.entities.size()));
                    game.addEntity(toAdd);
                    selectedEntity = toAdd;
                }

                if (selectedEntity && ImGui::BeginMenu("Add component")) {
                    for (auto& pair : decoratorFactoryMap) {
                        if (ImGui::MenuItem(pair.first.c_str())) {
                            nlohmann::json j;
                            pair.second(*selectedEntity, j);
                        }
                    }
                    ImGui::EndMenu();
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();

        }
        if (openSceneInputPopup) {
            ImGui::OpenPopup(sceneInputId);
        }

        if (ImGui::BeginPopupModal(sceneInputId)) {
            ImGui::InputText("Scene Path", currentSceneFileNameBuffer, 512);
            if (ImGui::Button("Save")) {
                currentSceneFileName.assign(currentSceneFileNameBuffer);
                std::filesystem::path cPath = std::filesystem::current_path() / currentSceneFileName;
                saveScene(cPath);
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }

        if ((!(ImGui::IsMouseDragging(ImGuiMouseButton_Left) && ImGui::IsItemHovered())) || entityDragged) {
            drawEntityEditor();
        }
    }

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
        json["origin"] = game.batcher->origin;
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

        Game& game = Game::instance<T>();

        game.clearEntities();

        for (nlohmann::json& entityJObject : entityArray) {
            if (entityJObject[Entity::componentArrayDecorator].is_null() || entityJObject["decorator"].get<std::string>() != Entity::jObjectDecorator) {
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Scene file corrupt: invalid entity.");
                return;
            }

            Entity* entity = new Entity(entityJObject["Name"]);
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

            game.addEntity(entity);
        }

        j["origin"].get_to(game.batcher->origin);

        currentSceneFileName = filename;
        stream.close();
    }
}