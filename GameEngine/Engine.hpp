/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-thomas.weinstein
** File description:
** Engine
*/

#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include "raylib.h"
#include <fstream>
#include "../ECS/Components.hpp"
#include <vector>

constexpr int SCREEN_WIDTH = 1200;
constexpr int SCREEN_HEIGHT = 1080;

class System;

class Engine {
    public:
        Engine();
        ~Engine();

        void quit();
        void init(std::vector<struct Settings> settings);
        void clean();

        void render();
        void update();
        void events();
        void drawMap();

        void unloadPlayer1();

        inline static Engine &get()
        {
            if(s_instance == nullptr){
                s_instance = new Engine();
            }
            return *s_instance;
        }

        inline bool isRunning() {
            return running;
        }

        std::string getWinner()
        {
            return _winner;
        }
        bool getWon()
        {
            return won;
        }
    private:
        Sound win_sound;
        Camera _camera;
        bool running;
        std::string _fd;
        std::fstream _file;
        std::vector<std::string> _map;
        static Engine *s_instance;
        Texture2D aha;
        std::size_t counterForWin;
        Texture2D _break;
        std::string _winner;
        bool won;
};

#endif /* !ENGINE_HPP_ */
