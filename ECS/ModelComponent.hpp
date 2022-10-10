/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-thomas.weinstein
** File description:
** ModelComponent
*/

#ifndef MODELCOMPONENT_HPP_
#define MODELCOMPONENT_HPP_

#include "raylib.h"
#include "raymath.h"
#include "../AssetsManager/AssetsLoader.hpp"
#include "TransformComponent.hpp"


class ModelComponent : public Component {
    public:
        ModelComponent() = default;
        ModelComponent(std::string modelid, std::string textureid, std::string animation, float scale, std::string name) : modelID(modelid), textureID(textureid), _sc(scale), animationID(animation), _name(name)
        {
        }
        ~ModelComponent()
        {
            UnloadModel(_model);
        }

        void init() override
        {
            animFrameCounter = 0;
            _sc = 0.5f;
            _angle = 0.0f;
            transform = &_entity->getComponent<TransformComponent>();
            _model = AssetManager::get().getModel(modelID);
            anim = AssetManager::get().getModelAnim(animationID);
            _model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = AssetManager::get().getTexture(textureID);
            color_number = 0;
            color.push_back(WHITE);
            color.push_back(DARKPURPLE);
            color.push_back(BLUE);
            color.push_back(YELLOW);
        }

        void draw() override
        {
            transform->scale = _sc;
            Color couleur = color.at(color_number);
            DrawModelEx(_model, transform->position, axis, _angle, scale, couleur);

        }

        void unload()
        {
            // Engine::get().unloadPlayer1();
        }
        Model getModel()
        {
            return _model;
        }

        std::string getName()
        {
            return _name;
        }

        float getAngle()
        {
            return _angle;
        }

        void setAngle(float angle)
        {
            _angle = angle;
        }

        void updateFrame()
        {
            animFrameCounter++;
            UpdateModelAnimation(_model, anim[1], animFrameCounter);
            if (animFrameCounter >= anim[1].frameCount)
                animFrameCounter = 0;
        }

        void updateFramePosBomb()
        {
            if (animFrameCounter < anim[3].frameCount) {
            UpdateModelAnimation(_model, anim[3], animFrameCounter);
            animFrameCounter++;
            }
        }
        void updateFrameDead()
        {
                if (animFrameCounter < anim[2].frameCount) {
                UpdateModelAnimation(_model, anim[2], animFrameCounter);
                animFrameCounter++;
                }
        }

    private:
        TransformComponent *transform;
        Model _model;
        ModelAnimation *anim;
        int animFrameCounter;
        Vector3 axis = {1.0f, 30.0f, 0.0f};
        Vector3 scale = {0.7f, 0.7f, 0.7f};
        std::string modelID;
        std::string animationID;
        std::string _name;
        std::vector<Color> color;
        int color_number;
        float _angle;
        float _sc;
        std::string textureID;
};

#endif /* !MODELCOMPONENT_HPP_ */
