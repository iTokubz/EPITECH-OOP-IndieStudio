/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-thomas.weinstein
** File description:
** AIComponent
*/

#ifndef AICOMPONENT_HPP_
#define AICOMPONENT_HPP_

#include "ECS.hpp"

#include "../Core/IA/ia.hpp"
#include "TransformComponent.hpp"
#include <vector>
#include "ModelComponent.hpp"
#include "SettingsPlayer.hpp"
#include "KeyboardControler.hpp"

class AIComponent : public Component {
    public:
        AIComponent(char id) : _id(id) {}
        ~AIComponent() = default;
        void init() override
        {
            ai = new Pnj();
            position = &_entity->getComponent<TransformComponent>();
            settings = &_entity->getComponent<SettingsPlayer>();
            model = &_entity->getComponent<ModelComponent>();
            collisionDown = false;
            collisionLeft = false;
            collisionRight = false;
            collisionUp = false;
            timer_loop = time(0);
            ai->setId(_id);
            ai->open();
            ai->getPosid();

        }
        void update() override
        {
            if (time(0) - timer_loop >= 1) {
                ai->whereCanGo();
                ai->whereGoing();
                if (ai->getDir() == 1 && settings->getIsAlive()) {
                    model->updateFrame();
                    position->velocity.z = 0.0f;
                    position->velocity.x = 0.1f;
                    model->setAngle(90.0f);
                    collisionLeft = true;
                    collisionDown = true;
                    collisionUp = true;
                }
                if (ai->getDir() == 2 && settings->getIsAlive()) {
                    model->updateFrame();
                    position->velocity.z = 0.0f;
                    position->velocity.x = -0.1f;
                    model->setAngle(-90.0f);
                    collisionRight = true;
                    collisionDown = true;
                    collisionUp = true;
                }
                if (ai->getDir() == 3 && settings->getIsAlive()) {
                    model->updateFrame();
                    position->velocity.x = 0.0f;
                    position->velocity.z = -0.1f;
                    model->setAngle(180.0f);
                    collisionDown = true;
                    collisionLeft = true;
                    collisionRight = true;
                }
                if (ai->getDir() == 4  && settings->getIsAlive() == false) {
                    model->updateFrame();
                    position->velocity.x = 0.0f;
                    position->velocity.z = 0.1f;
                    model->setAngle(0.0f);
                    collisionUp = true;
                    collisionLeft = true;
                    collisionRight = true;
                }
                for (auto &c : _entity->manager.getVectorEntitys()) {
                    if (c->hasComponent<KeyboardControler>()) {
                        KeyboardControler *control = &c->getComponent<KeyboardControler>();
                        if (control->getExploded() == true) {
                            TransformComponent *Position = &c->getComponent<TransformComponent>();
                            ModelComponent *modelC = &c->getComponent<ModelComponent>();
                            if ((control->getBombPos().x +3.5f >= Position->position.x && control->getBombPos().x -3.5f <= Position->position.x) && ((control->getBombPos().z + 0.5f >= Position->position.z && control->getBombPos().z - 0.5f <= Position->position.z)) ||
                                (control->getBombPos().z +3.5f >= Position->position.z && control->getBombPos().z -3.5f <= Position->position.z) && ((control->getBombPos().x + 0.5f >= Position->position.x && control->getBombPos().x - 0.5f <= Position->position.x))) {
                                    PlaySound(control->getSound());
                                    SettingsPlayer *set = &c->getComponent<SettingsPlayer>();
                                    modelC->updateFrameDead();
                                    set->getIsAlive() = false;
                                }
                        }
                    }
                }
                ai->placePnj();
                if (settings->getIsAlive()) {
                    position->velocity.x = 0;
                    position->velocity.y = 0;
                }
            }
            collisionLeft = false;
            collisionDown = false;
            collisionUp = false;
            collisionRight = false;
            timer_loop = time(0);
        }
    private:
        char _id;
        Pnj *ai;
        TransformComponent *position;
        ModelComponent *model;
        SettingsPlayer *settings;
        time_t timer_loop;
        bool collisionLeft;
        bool collisionDown;
        bool collisionUp;
        bool collisionRight;
};

#endif /* !AICOMPONENT_HPP_ */
