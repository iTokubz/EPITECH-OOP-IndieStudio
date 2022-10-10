/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-thomas.weinstein
** File description:
** MapComponent
*/

#ifndef MAPCOMPONENT_HPP_
#define MAPCOMPONENT_HPP_

#include <fstream>
#include "raylib.h"
#include "ECS.hpp"
#include "ModelComponent.hpp"
#include "TransformComponent.hpp"
// #include "KeyboardControler.hpp"
#include <cstdlib>

class MapComponent : public Component {
    public:
        MapComponent(std::string map_path, std::string textureSolid, std::string textureBreak, Entity &player1, Entity &player2, Entity &player3, Entity &player4) : _mapPath(map_path), _solidTexture(textureSolid), _textureBreak(textureBreak), _player1(player1), _player2(player2), _player3(player3), _player4(player4) {}
        ~MapComponent() = default;
        typedef struct
        {
            float lifeTime;
        }Timer;

        void startTimer(Timer *timer, float bonusLife)
        {
            if (timer != nullptr)
                timer->lifeTime = bonusLife;
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
            _file.open(_mapPath, std::ios::in);
            if(_file.is_open()) {
                while (std::getline(_file, _fd)) {
                    _map.push_back(_fd);
                }
            }
            bonus = LoadSound("Assets/bonus.wav");
            _solid = LoadTexture(_solidTexture.c_str());
            _break = LoadTexture(_textureBreak.c_str());
            boxSize = {2.0f, 2.0f, 2.0f};
            colliderPlayer1 = false;
            colliderPlayer2 = false;
            colliderPlayer3 = false;
            colliderPlayer4 = false;
            _playerSize = {1.0f, 1.0f, 1.0f};

            playerpos1 = &_player1.getComponent<TransformComponent>();
            player1 = &_player1.getComponent<ModelComponent>();
            playerpos2 = &_player2.getComponent<TransformComponent>();
            playermodel2 = &_player2.getComponent<ModelComponent>();
            playerpos3 = &_player3.getComponent<TransformComponent>();
            playermodel3 = &_player3.getComponent<ModelComponent>();
            playerpos4 = &_player4.getComponent<TransformComponent>();
            playermodel4 = &_player4.getComponent<ModelComponent>();
            animFrameCounter = 0;
            animCount = 0;
            bonusSpeedTex = LoadTexture("Assets/speedup_texture.png");
            bonusFireTex = LoadTexture("Assets/fire_txt.png");
            bonusWallPassTex = LoadTexture("Assets/wall_pass.png");
            bonusInvincibleTex = LoadTexture("Assets/invincible.png");

            bonusSpeed = LoadModel("Assets/speed_up.iqm");
            bonusFire = LoadModel("Assets/fire_up.iqm");
            bonusInvincible = LoadModel("Assets/invincible.iqm");
            bonusWallPass = LoadModel("Assets/wall_pass.iqm");
            animBonus = LoadModelAnimations("Assets/speed_up.iqm", &animCount);

            _grass = LoadModel("Assets/cool_grass.iqm");
            _grasstex = LoadTexture("Assets/grass_texture.png");
            _ground = LoadModel("Assets/ground.iqm");
            _groundtex = LoadTexture("Assets/ground_texture.png");
            // _bridge = LoadModel("Assets/woodenbridge.obj");
            // _bridgetex = LoadTexture("Assets/wood.png");
            bonusSpeed.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = bonusSpeedTex;
            bonusFire.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = bonusFireTex;
            bonusInvincible.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = bonusInvincibleTex;
            bonusWallPass.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = bonusWallPassTex;
            _ground.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _groundtex;
            _grass.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _grasstex;
            // _bridge.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _bridgetex;

            isBonus = false;

            bonuses.push_back(bonusSpeed);
            bonuses.push_back(bonusFire);
            bonuses.push_back(bonusInvincible);
            bonuses.push_back(bonusWallPass);
            bonusTimerSpeed = {0};
            bonusLifeSpeed = 5.0f;
            bonusTimerInvincible = {0};
            bonusTimerWall = {0};
            bonusLifeWall = 10.0f;
            bonusLifeInvincible = 10.0f;
        }

        void checkCollision()
        {
            if (colliderPlayer1 && _player1.isActive()) {
                if (player1->getAngle() == 90.0f)
                    playerpos1->position.x -= 0.1f;
                if (player1->getAngle() == -90.0f)
                    playerpos1->position.x += 0.1f;
                if (player1->getAngle() == 0.0f)
                    playerpos1->position.z -= 0.1f;
                if (player1->getAngle() == 180.0f)
                    playerpos1->position.z += 0.1f;
            }
            if (colliderPlayer2) {
                if (playermodel2->getAngle() == 90.0f)
                    playerpos2->position.x -= 0.1f;
                if (playermodel2->getAngle() == -90.0f)
                    playerpos2->position.x += 0.1f;
                if (playermodel2->getAngle() == 0.0f)
                    playerpos2->position.z -= 0.1f;
                if (playermodel2->getAngle() == 180.0f)
                    playerpos2->position.z += 0.1f;
            }
            if (colliderPlayer3) {
                if (playermodel3->getAngle() == 90.0f)
                    playerpos3->position.x -= 0.1f;
                if (playermodel3->getAngle() == -90.0f)
                    playerpos3->position.x += 0.1f;
                if (playermodel3->getAngle() == 0.0f)
                    playerpos3->position.z -= 0.1f;
                if (playermodel3->getAngle() == 180.0f)
                    playerpos3->position.z += 0.1f;
            }
            if (colliderPlayer4) {
                if (playermodel4->getAngle() == 90.0f)
                    playerpos4->position.x -= 0.1f;
                if (playermodel4->getAngle() == -90.0f)
                    playerpos4->position.x += 0.1f;
                if (playermodel4->getAngle() == 0.0f)
                    playerpos4->position.z -= 0.1f;
                if (playermodel4->getAngle() == 180.0f)
                    playerpos4->position.z += 0.1f;
            }
        }

        void draw() override
        {


            float a = -32.0f;
            float b = -29.0f;
            for (int i = 0; i < 9; i ++) {
                for (int j = 0; j < 13; j++) {
                    DrawModel(_grass, Vector3{a, -1.0f, b}, 1.8f, WHITE);
                    a += 5.3f;
                }
            b += 6.0f;
            a = -32.0f;
            }
            DrawModel(_ground, Vector3{0.0f, -1.0f, 0.0f}, 19.0f, DARKGREEN);
            for (auto& ligne: _map) {
                for (auto& caseboard : ligne) {
                    Vector3 enemyBoxPos = { x , y, z };
                    if (CheckCollisionBoxes(
            (BoundingBox){(Vector3){ playerpos1->position.x - _playerSize.x/2, playerpos1->position.y - _playerSize.y/2, playerpos1->position.z - _playerSize.z/2 },
                          (Vector3){ playerpos1->position.x + _playerSize.x/2, playerpos1->position.y + _playerSize.y/2, playerpos1->position.z + _playerSize.z/2 }},

            (BoundingBox){(Vector3){ enemyBoxPos.x - boxSize.x/2, enemyBoxPos.y - boxSize.y/2, enemyBoxPos.z - boxSize.z/2 },
                          (Vector3){ enemyBoxPos.x + boxSize.x/2, enemyBoxPos.y + boxSize.y/2, enemyBoxPos.z + boxSize.z/2 }}))
                          colliderPlayer1 = true; else colliderPlayer1 = false;
                    if (CheckCollisionBoxes(
            (BoundingBox){(Vector3){ playerpos2->position.x - _playerSize.x/2, playerpos2->position.y - _playerSize.y/2, playerpos2->position.z - _playerSize.z/2 },
                          (Vector3){ playerpos2->position.x + _playerSize.x/2, playerpos2->position.y + _playerSize.y/2, playerpos2->position.z + _playerSize.z/2 }},

            (BoundingBox){(Vector3){ enemyBoxPos.x - boxSize.x/2, enemyBoxPos.y - boxSize.y/2, enemyBoxPos.z - boxSize.z/2 },
                          (Vector3){ enemyBoxPos.x + boxSize.x/2, enemyBoxPos.y + boxSize.y/2, enemyBoxPos.z + boxSize.z/2 }}))
                          colliderPlayer2 = true; else colliderPlayer2 = false;
                    if (CheckCollisionBoxes(
            (BoundingBox){(Vector3){ playerpos3->position.x - _playerSize.x/2, playerpos3->position.y - _playerSize.y/2, playerpos3->position.z - _playerSize.z/2 },
                          (Vector3){ playerpos3->position.x + _playerSize.x/2, playerpos3->position.y + _playerSize.y/2, playerpos3->position.z + _playerSize.z/2 }},

            (BoundingBox){(Vector3){ enemyBoxPos.x - boxSize.x/2, enemyBoxPos.y - boxSize.y/2, enemyBoxPos.z - boxSize.z/2 },
                          (Vector3){ enemyBoxPos.x + boxSize.x/2, enemyBoxPos.y + boxSize.y/2, enemyBoxPos.z + boxSize.z/2 }}))
                          colliderPlayer3 = true; else colliderPlayer3 = false;
                    if (CheckCollisionBoxes(
            (BoundingBox){(Vector3){ playerpos4->position.x - _playerSize.x/2, playerpos4->position.y - _playerSize.y/2, playerpos4->position.z - _playerSize.z/2 },
                          (Vector3){ playerpos4->position.x + _playerSize.x/2, playerpos4->position.y + _playerSize.y/2, playerpos4->position.z + _playerSize.z/2 }},

            (BoundingBox){(Vector3){ enemyBoxPos.x - boxSize.x/2, enemyBoxPos.y - boxSize.y/2, enemyBoxPos.z - boxSize.z/2 },
                          (Vector3){ enemyBoxPos.x + boxSize.x/2, enemyBoxPos.y + boxSize.y/2, enemyBoxPos.z + boxSize.z/2 }}))
                          colliderPlayer4 = true; else colliderPlayer4 = false;
                    if (caseboard == 'X') {
                        checkCollision();
                        DrawCubeTexture(_solid,enemyBoxPos, boxSize.x, boxSize.y, boxSize.z, GRAY);
                        x += 2.0f;
                    }
                    else if (caseboard == 'O') {
                        checkCollision();
                        DrawCubeTexture(_break,enemyBoxPos, boxSize.x, boxSize.y, boxSize.z, WHITE);
                        if (isBonus == false) {
                            allBoxPos.push_back(enemyBoxPos);
                            randBonus = rand() % 3;
                        }
                        x += 2.0f;
                    }
                    else if (caseboard == '.')
                        x += 2.0f;
                }
                z += 2.0f;
                x = -13.0f;
            }
            if (isBonus == false) {
                bonuspos = allBoxPos.at(rand() % allBoxPos.size());
                modelAnimated = bonuses.at(randBonus);
                isBonus = true;
            }
            DrawModel(bonuses.at(randBonus), bonuspos, 2.0f, WHITE);
            allBoxPos.clear();
            animFrameCounter++;
            UpdateModelAnimation(modelAnimated, animBonus[0], animFrameCounter);
            if (animFrameCounter >= animBonus[0].frameCount) animFrameCounter = 0;
        }
        void update() override
        {
            if ((bonuspos.x + 1.0f >= playerpos1->position.x && bonuspos.x - 1.0f <= playerpos1->position.x) && ((bonuspos.z + 1.0f >= playerpos1->position.z && bonuspos.z - 1.0f <= playerpos1->position.z)) ||
            (bonuspos.z + 1.0f >= playerpos1->position.z && bonuspos.z - 1.0f <= playerpos1->position.z) && ((bonuspos.x + 1.0f >= playerpos1->position.x && bonuspos.x - 1.0f <= playerpos1->position.x))) {
                isBonus = false;
                PlaySound(bonus);
                if (randBonus == 0) {
                    startTimer(&bonusTimerSpeed, bonusLifeSpeed);
                    playerpos1->speed = 1.5f;
                }
                // if (randBonus == 2) {
                //     // sta
                // }
            }
            if ((bonuspos.x + 1.0f >= playerpos2->position.x && bonuspos.x - 1.0f <= playerpos2->position.x) && ((bonuspos.z + 1.0f >= playerpos2->position.z && bonuspos.z - 1.0f <= playerpos2->position.z)) ||
            (bonuspos.z + 1.0f >= playerpos2->position.z && bonuspos.z - 1.0f <= playerpos2->position.z) && ((bonuspos.x + 1.0f >= playerpos2->position.x && bonuspos.x - 1.0f <= playerpos2->position.x))) {
                isBonus = false;
                if (randBonus == 0) {
                    startTimer(&bonusTimerSpeed, bonusLifeSpeed);
                    playerpos2->speed = 1.5f;
                }
            }
            if ((bonuspos.x + 1.0f >= playerpos3->position.x && bonuspos.x - 1.0f <= playerpos3->position.x) && ((bonuspos.z + 1.0f >= playerpos3->position.z && bonuspos.z - 1.0f <= playerpos3->position.z)) ||
            (bonuspos.z + 1.0f >= playerpos3->position.z && bonuspos.z - 1.0f <= playerpos3->position.z) && ((bonuspos.x + 1.0f >= playerpos3->position.x && bonuspos.x - 1.0f <= playerpos3->position.x))) {
                isBonus = false;
                if (randBonus == 0) {
                    startTimer(&bonusTimerSpeed, bonusLifeSpeed);
                    playerpos3->speed = 1.5f;
                }
            }
            if ((bonuspos.x + 1.0f >= playerpos4->position.x && bonuspos.x - 1.0f <= playerpos4->position.x) && ((bonuspos.z + 1.0f >= playerpos4->position.z && bonuspos.z - 1.0f <= playerpos4->position.z)) ||
            (bonuspos.z + 1.0f >= playerpos4->position.z && bonuspos.z - 1.0f <= playerpos4->position.z) && ((bonuspos.x + 1.0f >= playerpos4->position.x && bonuspos.x - 1.0f <= playerpos4->position.x))) {
                isBonus = false;
                if (randBonus == 0) {
                    startTimer(&bonusTimerSpeed, bonusLifeSpeed);
                    playerpos4->speed = 1.5f;
                }
            }
            x = -13.0f;
            y = 1.0f;
            z = -11.0f;
            if (randBonus == 0)
                updateTime(&bonusTimerSpeed);
            // if (randBonus == 2)
                // up
            if (TimerDone(&bonusTimerSpeed)) {
                playerpos1->speed = 1.0f;
                playerpos2->speed = 1.0f;
                playerpos3->speed = 1.0f;
                playerpos4->speed = 1.0f;
            }
        }

        std::vector<std::string> &getMap()
        {
            return _map;
        }
    private:
        //////Graphics//////
        Model _grass;
        Model _ground;
        Texture2D _grasstex;
        Texture2D _groundtex;
        /////////////////////

        std::fstream _file;
        std::vector<std::string> _map;
        std::string _fd;
        std::string _solidTexture;
        std::string _textureBreak;
        std::string _mapPath;
        Texture2D _solid;
        Texture2D _break;
        float x;
        float y;
        float z;
        unsigned int animCount;
        int animFrameCounter;
        Vector3 boxSize;
        Vector3 boxPos;
        bool colliderPlayer1;
        float bonusLifeSpeed;
        float bonusLifeInvincible;
        Timer bonusTimerWall;
        float bonusLifeWall;
        Timer bonusTimerInvincible;
        Timer bonusTimerSpeed;
        bool colliderPlayer2;
        bool colliderPlayer3;
        bool colliderPlayer4;
        TransformComponent *playerpos1;
        ModelComponent *player1;
        Vector3 _playerSize;
        bool isBonus;
        Entity &_player1;
        Entity &_player2;
        Model bonusSpeed;
        Model bonusWallPass;
        Model bonusFire;
        Model bonusInvincible;
        Model modelAnimated;
        Texture2D bonusSpeedTex;
        Texture2D bonusWallPassTex;
        std::vector<Model> bonuses;
        Texture2D bonusFireTex;
        Texture2D bonusInvincibleTex;
        Entity &_player3;
        Entity &_player4;
        TransformComponent *playerpos3;
        TransformComponent *playerpos4;
        Vector3 bonuspos;
        ModelComponent *playermodel3;
        ModelAnimation *animBonus;
        int randBonus;
        std::vector<Vector3> allBoxPos;
        ModelComponent *playermodel4;
        TransformComponent *playerpos2;
        ModelComponent *playermodel2;
        Sound bonus;
};

#endif /* !MAPCOMPONENT_HPP_ */
