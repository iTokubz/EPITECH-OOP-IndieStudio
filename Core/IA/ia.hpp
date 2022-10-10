/*
** EPITECH PROJECT, 2022
** ia
** File description:
** ia
*/

#ifndef IA_HPP_
#define IA_HPP_
#include <utility>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
 #include <cstdlib>
#include <ctime>
#include <random>
#include <cstdio>
#include <ctime>
#include <thread>
#include <chrono>

class Pnj {
    enum dir {
        RIGHT = 1,
        LEFT = 2,
        UP = 3,
        DOWN = 4,
    };
    public:
        Pnj();
        ~Pnj();
        void globalLoop();
        void open();
        void getPosid();
        void whereCanGo();
        void whereGoing();
        void setId(char id);
        int &getDir();
        void moveIA(int);
        void placePnj();
        int findMax();
        int findMin();
        void shouldDrop();
        void Run();
        void destroyMap();
        inline static Pnj &get()
        {
            if(s_instance == nullptr) {
                s_instance = new Pnj();
            }
            return *s_instance;
        }
    private:
        char _id;
        bool _alive;
        std::fstream _file;
        std::vector<std::string> _map;
        static Pnj *s_instance;
        std::pair<int, int> _pos;
        float _speed;
        std::pair<int, std::vector<int>> _possible_mov;
        int _dir;
        int _lastDir;
        bool _isBomb;
        int _inc;
        std::pair<int, int> _pos_bomb;
};

#endif /* !IA_HPP_ */
