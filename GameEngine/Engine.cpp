/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-thomas.weinstein
** File description:
** Engine
*/

#include "Engine.hpp"
#include "../AssetsManager/AssetsLoader.hpp"
#include "Settings.hpp"
#include "../ECS/ECS.hpp"
#include "../ECS/TransformComponent.hpp"
#include "../ECS/ModelComponent.hpp"
#include "../ECS/SettingsPlayer.hpp"
#include "../ECS/KeyboardControler.hpp"
#include "../ECS/MapController.hpp"
#include "../ECS/AIComponent.hpp"
#include "raymath.h"

Engine *Engine::s_instance = nullptr;
System ecs;
auto &Player(ecs.addEntity());
auto &Player2(ecs.addEntity());
auto &Player3(ecs.addEntity());
auto &Player4(ecs.addEntity());
auto &Map(ecs.addEntity());

enum groupLabels : std::size_t
{
    groupPlayer,
    groupMap
};

Engine::Engine() : running(false)
{
}

Engine::~Engine()
{
}

void Engine::init(std::vector<struct Settings> settings)
{
    won = false;
    int nbrPlayer = 3;
    int incrementSettings = 0;
    std::vector<KeyboardKey> settings_players = {KEY_UP, KEY_DOWN, KEY_RIGHT, KEY_LEFT, KEY_SPACE, KEY_Z, KEY_S, KEY_D, KEY_Q, KEY_LEFT_ALT, KEY_T, KEY_G, KEY_H, KEY_F, KEY_N, KEY_KP_8, KEY_KP_5, KEY_KP_6, KEY_KP_4, KEY_KP_0};
    for (auto &c : settings) {
        if (c._keyUp != 0)
            settings_players.at(incrementSettings) = (KeyboardKey)c._keyUp;
        ++incrementSettings;
        if (c._keyDown != 0)
            settings_players.at(incrementSettings) = (KeyboardKey)c._keyDown;
        ++incrementSettings;
        if (c._keyRight != 0)
            settings_players.at(incrementSettings) = (KeyboardKey)c._keyRight;
        ++incrementSettings;
        if (c._keyLeft != 0)
            settings_players.at(incrementSettings) = (KeyboardKey)c._keyLeft;
        ++incrementSettings;
        if (c._keyBomb != 0)
            settings_players.at(incrementSettings) = (KeyboardKey)c._keyBomb;
        ++incrementSettings;
    }
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Indie");
    SetTargetFPS(60);
    _camera = { { 0.0f, 28.0f, 10.0f }, { 0.0f, -5.0f, 0.0f }, { 0.0f, 10.0f, -10.0f }, 85.0f, 0 };
    unsigned int animsCount = 0;
    win_sound = LoadSound("Assets/win.wav");
    AssetManager::get().loadTextureAssets("player", "Assets/Muhammer.png");
    AssetManager::get().loadModelAssets("player", "Assets/5.iqm");
    AssetManager::get().loadModelAnims("player", "Assets/5.iqm", animsCount);
    AssetManager::get().loadTextureAssets("player2", "Assets/Muhammer.png");
    AssetManager::get().loadModelAssets("player2", "Assets/5.iqm");
    AssetManager::get().loadModelAnims("player2", "Assets/5.iqm", animsCount);
    AssetManager::get().loadTextureAssets("player3", "Assets/Muhammer.png");
    AssetManager::get().loadModelAssets("player3", "Assets/5.iqm");
    AssetManager::get().loadModelAnims("player3", "Assets/5.iqm", animsCount);
    AssetManager::get().loadTextureAssets("player4", "Assets/Muhammer.png");
    AssetManager::get().loadModelAssets("player4", "Assets/5.iqm");
    AssetManager::get().loadModelAnims("player4", "Assets/5.iqm", animsCount);
    float positionZ = 2.0f;

    running = true;
    std::size_t id = 0;
    Player.addComponent<SettingsPlayer>();
    Player.addComponent<TransformComponent>(-11.0f, 1.0f, -8.5f, 0.3f);
    Player.addComponent<ModelComponent>("player", "player", "player", 0.3f, "Player 1");
    if (settings.at(0)._AI == false)
        Player.addComponent<KeyboardControler>(settings_players.at(id), settings_players.at(id+1), settings_players.at(id+2), settings_players.at(id+3), settings_players.at(id+4));
    else {
        Player.addComponent<AIComponent>('1');
        Player.addComponent<KeyboardControler>();
    }
    id += 5;
    Player2.addComponent<SettingsPlayer>();
    Player2.addComponent<TransformComponent>(13.0f, 1.0f, -8.5f, 0.3f);
    Player2.addComponent<ModelComponent>("player2", "player2","player2", 0.3f, "Player 2");
    if (settings.at(1)._AI == false)
        Player2.addComponent<KeyboardControler>(settings_players.at(id), settings_players.at(id+1), settings_players.at(id+2), settings_players.at(id+3), settings_players.at(id+4));
    else {
        Player2.addComponent<AIComponent>('2');
        Player2.addComponent<KeyboardControler>();
    }
    Player2.addGroup(groupPlayer);
    id+=5;
    Player3.addComponent<SettingsPlayer>();
    Player3.addComponent<TransformComponent>(13.0f, 1.0f, 9.2f, 0.3f);
    Player3.addComponent<ModelComponent>("player3", "player3", "player3", 0.3f, "Player 3");
    if (settings.at(2)._AI == false)
        Player3.addComponent<KeyboardControler>(settings_players.at(id), settings_players.at(id+1), settings_players.at(id+2), settings_players.at(id+3), settings_players.at(id+4));
    else {
        Player3.addComponent<AIComponent>('3');
        Player3.addComponent<KeyboardControler>();
    }
    Player3.addGroup(groupPlayer);
    id+=5;
    Player4.addComponent<SettingsPlayer>();
    Player4.addComponent<TransformComponent>(-11.0f, 1.0f, 9.2f, 0.3f);
    Player4.addComponent<ModelComponent>("player4", "player4", "player4", 0.3f, "Player 4");
    if (settings.at(3)._AI == false)
        Player4.addComponent<KeyboardControler>(settings_players.at(id), settings_players.at(id+1), settings_players.at(id+2), settings_players.at(id+3), settings_players.at(id+4));
    else {
        Player4.addComponent<AIComponent>('4');
        Player4.addComponent<KeyboardControler>();
    }
    Player4.addGroup(groupPlayer);

    Map.addComponent<MapComponent>("Assets/map.txt", "Assets/wall.png", "Assets/break.png", Player, Player2, Player3, Player4);
    Player.addComponent<MapController>(Map);
    Player2.addComponent<MapController>(Map);
    Player3.addComponent<MapController>(Map);
    Player4.addComponent<MapController>(Map);
    Player.addGroup(groupPlayer);
    Map.addGroup(groupMap);
}

void Engine::unloadPlayer1()
{
    Player.delGroup(groupPlayer);
    Player.destroy();
}

void Engine::render()
{
    auto &Players(ecs.getGroup(groupPlayer));
    auto &Maps(ecs.getGroup(groupMap));
    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode3D(_camera);
    for (auto &t : Players) {
        t->draw();
    }
    for (auto &m : Maps) {
        m->draw();
    }
    EndMode3D();
    EndDrawing();
}

void Engine::update()
{
    ecs.refresh();
    ecs.update();

    for (auto &e : ecs.getVectorEntitys()) {
        if (e->hasComponent<SettingsPlayer>()) {
            SettingsPlayer *settings = &e->getComponent<SettingsPlayer>();
                if (settings->getIsAlive() == false)
                    ++counterForWin;
        }
    }
    if (counterForWin == 3) {
        for (auto &e : ecs.getVectorEntitys()) {
            SettingsPlayer *settings = &e->getComponent<SettingsPlayer>();
            if (settings->getIsAlive()) {
                PlaySound(win_sound);
                ModelComponent *name = &e->getComponent<ModelComponent>();
                _winner = name->getName() + "won the game\n";
                break;
            }
        }
    }
    if (counterForWin == 3) {
        won = true;
        quit();
    }
    counterForWin = 0;
}

void Engine::events()
{
    if (IsKeyPressed(KEY_ESCAPE))
        this->quit();
}

void Engine::clean()
{
}

void Engine::quit()
{
    running = false;
}