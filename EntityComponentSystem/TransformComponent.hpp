/*
** EPITECH PROJECT, 2022
** EntityComponentSystem
** File description:
** TransformComponent
*/

#ifndef TRANSFORMCOMPONENT_HPP_
#define TRANSFORMCOMPONENT_HPP_

#include "Entity.hpp"
#include "Component.hpp"
#include "raylib.h"

class TransformComponent : public Component
{
    public:
        Vector3 position;
        Vector3 velocity;
        float scale = 1.0f;
        float speed = 3.0f;

        TransformComponent() = default;

        TransformComponent(float x, float y, float z, float sc)
        {
           position = {x, y, z};
        }
        bool init() override
        {
            velocity.x = 0;
            velocity.z = 0;
        }

        void update() override
        {
            position.x += velocity.x * speed;
            position.z += velocity.z * speed;
        }
};

#endif /* !TRANSFORMCOMPONENT_HPP_ */
