/*
** EPITECH PROJECT, 2022
** map
** File description:
** map
*/

#ifndef MAP_HPP_
#define MAP_HPP_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Map {
    public:
        Map();
        ~Map();
        void safeMap();
        void resetSafe();
        void randomisator();
    private:
        std::string _fd;
        std::fstream _file;
        std::vector<std::string> _map;
        std::vector<std::string> _mapSave;
};

#endif /* !MAP_HPP_ */
