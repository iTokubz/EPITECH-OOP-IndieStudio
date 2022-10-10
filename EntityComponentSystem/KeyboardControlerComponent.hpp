/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-thomas.weinstein
** File description:
** KeyboardControlerComponent
*/

#ifndef KEYBOARDCONTROLERCOMPONENT_HPP_
#define KEYBOARDCONTROLERCOMPONENT_HPP_

#include "Entity.hpp"
#include "Component.hpp"
#include "raylib.h"

class KeyboardControlerComponent : public Component {
    public:
        bool init() override
        {
            _transform = &entity->getComponent<TransformComponent>();
        }
        void update() override
        {
            if (IsKeyDown(KEY_RIGHT)) {
                _transform->velocity.z = 0;
                _transform->velocity.x = 1;
            }
            if (IsKeyDown(KEY_LEFT)) {
                _transform->velocity.z = 0;
                _transform->velocity.x = -1;
            }
            if (IsKeyDown(KEY_UP)) {
                _transform->velocity.x = 0;
                _transform->velocity.z = -1;
            }
            if (IsKeyDown(KEY_DOWN)) {
                _transform->velocity.x = 0;
                _transform->velocity.z = 1;
            }
        }
    private:
        TransformComponent *_transform;
};

#endif /* !KEYBOARDCONTROLERCOMPONENT_HPP_ */
