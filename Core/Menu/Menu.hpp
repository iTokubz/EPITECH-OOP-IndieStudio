//
// Created by matteom on 02/06/22.
//

#ifndef B_YEP_400_STG_4_1_INDIESTUDIO_THOMAS_WEINSTEIN_MENU_HPP
#define B_YEP_400_STG_4_1_INDIESTUDIO_THOMAS_WEINSTEIN_MENU_HPP
#include "raylib.h"
#include <iostream>
#include <sstream>
#include "../../GameEngine/Settings.hpp"
#include <vector>

constexpr int screenWidth = 1920;
constexpr int screenHeight = 1080;

class Menu {
    public:
        Menu();
        ~Menu();
        void StartMenu();
        void init();
        void Event_Handler();
        static void DrawMenu();
        void Parallax_init();
        void Drawing();
        void bind_keys();
        void DrawSettings();
        bool getRunningMenu() { return runningMenu;}
        bool getGameIsOpen() {return is_game_open;}
        bool getSettingsIsOpen() {return is_settings_open;}
        void EventSettings();
        std::vector<struct Settings> &getSettings() {return _settings;}
        void Drawparallax();
    private:
        int i = 0;
        bool is_menu_open;
        bool is_game_open;
        int players;
        Texture2D texture;
        bool is_players_1;
        bool is_players_2;
        bool is_players_3;
        bool is_players_4;
        int playerVectorPosition;
        bool is_settings_open;
        float FrameHeight;
        Rectangle SourceRec ;
        Rectangle button_exit;
        Rectangle button_return;
        Rectangle button_2;
        Rectangle button_3;
        Rectangle button_4;
        Rectangle button_5;
        Rectangle button_6;
        Rectangle button_IA;
        Rectangle button_player;
        bool is_ia = false;
        Color IA = RED;
        std::vector<struct Settings> _settings;
        Texture2D exit_button;
        Texture2D loadgame_button;
        Texture2D newgame_button;
        Texture2D settings_button;
        Texture2D texture_parallax1;
        Texture2D texture_parallax2;
        Texture2D texture_parallax3;
        Texture2D texture_parallax4;
        Texture2D texture_parallax5;
        Texture2D texture_logo;
        Vector2 offset = {0, 0};
        Vector2 offset2 = {0, 0};
        Vector2 offset3 = {0, 0};
        bool runningMenu;
        Vector2 offset4 = {0, 0};
        Vector2 offset5 = {0, 0};
        Vector2 Mouse = {0, 0};
        Vector2 LocationButton = {1680, 980};
        bool ButtonAction = false;
        int ButtonState = 0;
        int key;
        int status;
        int vectorSettingsPointing;
        int Key_bomb;
        int BombBindAble;
        int key_up;
        int upBindAble;
        int key_down;
        int downBindAble;
        int key_left;
        int leftBindAble;
        int key_right;
        int rightBindAble;
        bool getKeyBomb;
        Vector2 LocationTextExit = {913, 530};
        Vector2 LocationLoadGame = {913, 685};
        Vector2 LocationNewGame = {913, 610};
        Vector2 LocationSettings = {910, 765 };
        Sound Click;
        Music back_menu;
        std::vector<char *> _player;
};

#endif //B_YEP_400_STG_4_1_INDIESTUDIO_THOMAS_WEINSTEIN_MENU_HPP
