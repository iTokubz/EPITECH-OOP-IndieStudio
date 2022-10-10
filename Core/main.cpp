//
// Created by matteom on 31/05/22.
//

#include <cstdio>
#include "raylib.h"
#include "Menu/Menu.hpp"
#include "Core.hpp"

int main(int argc, char** argv)
{
    Menu menu;
    InitWindow(screenWidth, screenHeight, "Indie Studio");
    InitAudioDevice();
    Core core;

    SetTargetFPS(1000);

    menu.init();

    while (menu.getRunningMenu())
    {
        menu.StartMenu();
        menu.Event_Handler();
        menu.Parallax_init();
        if (menu.getSettingsIsOpen())
        {
            ClearBackground(RAYWHITE);
        }
        if (menu.getGameIsOpen()) {
            CloseWindow();
            core.startGame(menu.getSettings());
        }
    }
    CloseWindow();
    return 0;
}