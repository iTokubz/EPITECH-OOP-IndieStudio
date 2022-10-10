/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-thomas.weinstein
** File description:
** ModelComponent
*/

#ifndef MODELCOMPONENT_HPP_
#define MODELCOMPONENT_HPP_

#include "Component.hpp"
#include "Entity.hpp"
#include "raylib.h"
#include "../AssetsManager/AssetsLoader.hpp"


class ModelComponent : public Component {
    public:
        ModelComponent() = default;
        ModelComponent(std::string modelid, std::string textureid) : modelID(modelid), textureID(textureid)
        {
        }
        ~ModelComponent()
        {
            UnloadModel(_model);
        }

        bool init() override
        {
            transform = &entity->getComponent<TransformComponent>();
            _model = AssetManager::get().getModel(modelID);
            _model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = AssetManager::get().getTexture(textureID);
        }

        void draw() override
        {
            DrawModel(_model, transform->position, transform->scale, RAYWHITE);
            DrawRectangle(100,1,1,300, RED);
            DrawGrid(10, 1.0f);
            std::cout << "drawing!" << std::endl;
        }

    private:
        TransformComponent *transform;
        Model _model;
        std::string modelID;
        std::string textureID;
};

#endif /* !MODELCOMPONENT_HPP_ */
