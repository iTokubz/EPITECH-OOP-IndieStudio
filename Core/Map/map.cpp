/*
** EPITECH PROJECT, 2022
** map.cpp
** File description:
** map
*/

#include "map.hpp"

Map::Map()
{
    _file.open("../../map.txt", std::ios::in);
    if(_file.is_open()) {
        while (std::getline(_file, _fd)) {
            _map.push_back(_fd);
        }
    }
}

Map::~Map()
{
    _file.close();
}

void Map::randomisator()
{
    int is_obstacle = 0;

    for (auto& ligne: _map) {
        for (auto& caseboard : ligne) {
            if (caseboard == '.') {
                is_obstacle = random() % 2;
                if (is_obstacle == 0)
                    caseboard = 'O';
            }
            if (caseboard == ';')
                caseboard = '.';
        }
    }
}

void Map::safeMap()
{
    std::ofstream _fileSave("../../Save/save.txt", std::ios::in);

    _mapSave = _map;
    for (auto j : _map) {
        _fileSave << j << std::endl;
    }
    _fileSave.close();
}

void Map::resetSafe()
{
    std::ofstream _fileSave("../../Save/save.txt", std::ofstream::trunc);
    _fileSave.close();
}