/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-thomas.weinstein
** File description:
** KeyboardControlerComponent
*/

#ifndef KEYBOARDCONTROLERCOMPONENT_HPP_
#define KEYBOARDCONTROLERCOMPONENT_HPP_

#include "raymath.h"
#include "raylib.h"
#include <unistd.h>
#include "TransformComponent.hpp"
#include "SettingsPlayer.hpp"
#include "ECS.hpp"

class KeyboardControler : public Component {
    public:
        KeyboardControler(KeyboardKey up, KeyboardKey down, KeyboardKey right, KeyboardKey left, KeyboardKey bomb) : _up(up), _down(down), _right(right), _left(left), _bomb(bomb) {}
        KeyboardControler() {}
        ~KeyboardControler() = default;
        typedef struct
        {
            float lifeTime;
        }Timer;

        void startTimer(Timer *timer, float bombLife)
        {
            if (timer != nullptr)
                timer->lifeTime = bombLife;
        }

        void updateTime(Timer *timer)
        {
            if (timer != nullptr && timer->lifeTime > 0)
                timer->lifeTime -= GetFrameTime();
        }

        bool TimerDone(Timer *timer)
        {
            if (timer != nullptr)
                return timer->lifeTime <= 0;
        }

        void init() override
        {
            _transform = &_entity->getComponent<TransformComponent>();
            model = &_entity->getComponent<ModelComponent>();
            AssetManager::get().loadTextureAssets("explo", "Assets/BomberManEffect.png");
            AssetManager::get().loadTextureAssets("bomb", "Assets/bomb_texture.png");
            AssetManager::get().loadModelAssets("bomb", "Assets/bomb.iqm");
            bomb = AssetManager::get().getModel("bomb");
            death = LoadSound("Assets/death.wav");
            explosion = LoadSound("Assets/explosion.wav");
            bomb.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = AssetManager::get().getTexture("bomb");
            settings = &_entity->getComponent<SettingsPlayer>();
            for (int i = 0; i != settings->getBombsNbr(); ++i) {
                Texture2D tex = LoadTexture("Assets/bomb_texture.png");
                Model model = LoadModel("Assets/bomb.iqm");
                model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = tex;
                _bombsInventory.push_back(model);
            }
            bomber = 0;
            bombLife = 1.5f;
            exploLife = 0.7f;
            ballTimer = {0};
            exploTimer = {0};
            bombs = -1;

            frameWidth = (float)(AssetManager::get().getTexture("explo").width/7);   // Sprite one frame rectangle width
            frameHeight = (float)(AssetManager::get().getTexture("explo").height/3);           // Sprite one frame rectangle height
            currentFrame = 0;
            currentLine = 0;
            framesCounter = 0;
            collisionUp = false;
            collisionDown = false;
            collisionLeft = false;
            collisionRight = false;
            exploded = false;

            frameRec = { 0, 0, frameWidth, frameHeight };
            bombPlaced = false;
            position = { 0.0f, 0.0f };

            active = false;
        }
        void update() override
        {
            if (IsKeyDown(_right) && collisionRight == false && settings->getIsAlive()) {
                model->updateFrame();
                _transform->velocity.z = 0.0f;
                _transform->velocity.x = 0.1f;
                model->setAngle(90.0f);
                collisionLeft = true;
                collisionDown = true;
                collisionUp = true;
            }

            else if (IsKeyDown(_left) && collisionLeft == false && settings->getIsAlive()) {
                model->updateFrame();
                _transform->velocity.z = 0.0f;
                _transform->velocity.x = -0.1f;
                model->setAngle(-90.0f);
                collisionRight = true;
                collisionDown = true;
                collisionUp = true;
            }
            else if (IsKeyDown(_up) && collisionUp == false && settings->getIsAlive()) {
                model->updateFrame();
                _transform->velocity.x = 0.0f;
                _transform->velocity.z = -0.1f;
                model->setAngle(180.0f);
                collisionDown = true;
                collisionLeft = true;
                collisionRight = true;
            }
            else if (IsKeyDown(_down) && collisionDown == false && settings->getIsAlive()) {
                model->updateFrame();
                _transform->velocity.x = 0.0f;
                _transform->velocity.z = 0.1f;
                model->setAngle(0.0f);
                collisionUp = true;
                collisionLeft = true;
                collisionRight = true;
            }
            if (IsKeyReleased(_left)) {
                _transform->velocity.x = 0;
                collisionRight = false;
                collisionDown = false;
                collisionUp = false;
            }
            if (IsKeyReleased(_up)) {
                _transform->velocity.z = 0;
                collisionDown = false;
                collisionLeft = false;
                collisionRight = false;
            }
            if (IsKeyReleased(_right)) {
                collisionLeft = false;
                collisionDown = false;
                collisionUp = false;
                _transform->velocity.x = 0;
            }
            if (IsKeyReleased(_down)) {
                _transform->velocity.z = 0;
                collisionLeft = false;
                collisionUp = false;
                collisionRight = false;
            }
        }
        void draw() override
        {
            if (_entity->hasComponent<SettingsPlayer>()) {
                if (IsKeyPressed(_bomb) && ! active && settings->getIsAlive() && bomber == 0) {
                    if (bombs == 1)
                        bombs = -1;
                    bomber = 1;
                    model->updateFramePosBomb();
                    bombpos = _transform->position;
                    bombPlaced = true;
                    startTimer(&ballTimer, bombLife);
                    exploTimer = {0};
                    ++bombs;
                    active = true;
                    animexplo = false;

                }
                if (active) {
                    framesCounter++;
                    if (framesCounter > 3) {
                        currentFrame++;
                    if (currentFrame >= 7) {
                    currentFrame = 0;
                    currentLine++;
                    if (currentLine >= 3){
                        currentLine = 0;
                        active = false;
                    }
                    }
                framesCounter = 0;
                }
                frameRec.x = frameWidth*currentFrame;
                frameRec.y = frameHeight*currentLine;
                }
                if (bomber != 0) {
                    updateTime(&ballTimer);
                    if (!TimerDone(&ballTimer)) {
                        DrawModel(_bombsInventory.at(bombs), bombpos, 1.0f, RAYWHITE);
                        exploded = false;
                    }
                    if (TimerDone(&ballTimer) && animexplo == false) {
                        PlaySound(explosion);
                        startTimer(&exploTimer, exploLife);
                        setAllEntitys(true);
                        animexplo = true;
                        bombPlaced = false;
                        exploded = true;
                        settings->setMap(bombpos.x, bombpos.z);
                    }
                    for (auto &c : _entity->manager.getVectorEntitys()) {
                        if (c->hasComponent<KeyboardControler>()) {
                            KeyboardControler *control = &c->getComponent<KeyboardControler>();
                            if (control->getExploded() == true) {
                                TransformComponent *Position = &c->getComponent<TransformComponent>();
                                ModelComponent *modelC = &c->getComponent<ModelComponent>();
                                if ((getBombPos().x +3.5f >= Position->position.x && getBombPos().x -3.5f <= Position->position.x) && ((getBombPos().z + 0.5f >= Position->position.z && getBombPos().z - 0.5f <= Position->position.z)) ||
                                (getBombPos().z +3.5f >= Position->position.z && getBombPos().z -3.5f <= Position->position.z) && ((getBombPos().x + 0.5f >= Position->position.x && getBombPos().x - 0.5f <= Position->position.x))) {
                                    PlaySound(death);
                                    SettingsPlayer *set = &c->getComponent<SettingsPlayer>();
                                    modelC->updateFrameDead();
                                    set->getIsAlive() = false;
                                }
                            }
                        }
                    }
                    updateTime(&exploTimer);
                    if (!TimerDone(&exploTimer) && animexplo == true) {
                        active = true;
                        position.x -= frameWidth/10.0f;
                        position.y -= frameHeight/10.0f;
                        DrawCubeTextureRec(AssetManager::get().getTexture("explo"), frameRec, bombpos, 6.0f, 0.0f,6.0f, WHITE);
                    }
                    if (TimerDone(&exploTimer) && animexplo == true) {
                        animexplo = false;
                        bomber = 0;
                        active = false;
                        setAllEntitys(false);
                    }
                }
            }
        }

        void setExploded(bool state)
        {
            exploded = state;
        }

        void setAllEntitys(bool state)
        {
            for (auto &c : _entity->manager.getVectorEntitys()) {
                if (c->hasComponent<KeyboardControler>()) {
                    KeyboardControler *control = &c->getComponent<KeyboardControler>();
                    control->setExploded(state);
                }
            }
        }

        bool getExploded()
        {
            return exploded;
        }

        Vector3 getBombPos()
        {
            return bombpos;
        }
        Sound getSound()
        {
            return death;
        }
    private:
        TransformComponent *_transform;
        ModelComponent *model;
        SettingsPlayer *settings;
        std::size_t bombs;
        Vector3 bombpos;
        Model bomb;
        Texture2D bombtex;
        bool bombPlaced;
        std::size_t bomber;
        KeyboardKey _up;
        float bombLife;
        float exploLife;
        Timer ballTimer;
        Timer exploTimer;
        Texture2D explo;
        Rectangle frameRec;
        Vector2 position;
        bool animexplo;
        float frameWidth;
        float frameHeight;          // Sprite one frame rectangle height
        int currentFrame ;
        int currentLine ;
        int framesCounter ;
        bool collisionRight;
        bool collisionLeft;
        bool collisionUp;
        bool exploded;
        bool collisionDown;
        bool active;
        std::vector<std::string> _map;
        KeyboardKey _down;
        KeyboardKey _left;
        KeyboardKey _bomb;
        std::vector<Model> _bombsInventory;
        KeyboardKey _right;
        Sound explosion;
        Sound death;
};

#endif /* !KEYBOARDCONTROLERCOMPONENT_HPP_ */
