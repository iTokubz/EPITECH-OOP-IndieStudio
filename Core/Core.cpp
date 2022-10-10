/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-thomas.weinstein
** File description:
** Core
*/

#include "Core.hpp"
#include "../GameEngine/Engine.hpp"
#include "raylib.h"
#include <iostream>

Core::Core()
{

}

Core::~Core()
{
}

void Core::startGame(std::vector<struct Settings> settings)
{
    Engine &engine = Engine::get();
    engine.init(settings);

    while (engine.isRunning()) {
        engine.events();
        engine.update();
        engine.render();
    }
    engine.clean();
    if (engine.getWon()) {
        InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Indie");
        while (1) {
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText(engine.getWinner().c_str(), 200, 200, 40, LIGHTGRAY);
            EndDrawing();
        }
    }
    return;
}

