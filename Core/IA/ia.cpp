/*
** EPITECH PROJECT, 2022
** ia
** File description:
** ia
*/

#include "ia.hpp"

Pnj::Pnj() : _speed(0.2f), _alive(true), _lastDir(0), _inc(0), _isBomb(false)
{
}

Pnj::~Pnj()
{
    _alive = false;
}

void Pnj::open()
{
    _file.open("Save/save.txt", std::ios::in);
    std::string temp;
    if(_file.is_open()) {
        while (std::getline(_file, temp)) {
            _map.push_back(temp);
        }
    }
}

void Pnj::setId(char id)
{
    _id = id;
}

void Pnj::destroyMap()
{
    if (_map[_pos_bomb.first][_pos_bomb.second + 1] == 'O')
        _map[_pos_bomb.first][_pos_bomb.second + 1] = '.';
    if (_map[_pos_bomb.first][_pos_bomb.second - 1] == 'O') //left
        _map[_pos_bomb.first][_pos_bomb.second - 1] = '.';
    if (_map[_pos_bomb.first - 1][_pos_bomb.second] == 'O') //UP
        _map[_pos_bomb.first - 1][_pos_bomb.second] = '.';
    if (_map[_pos_bomb.first + 1][_pos_bomb.second] == 'O')
        _map[_pos_bomb.first + 1][_pos_bomb.second] = '.';
    _isBomb = false;
}

void Pnj::shouldDrop()
{
    int count = 0;

    if (_map[_pos.first][_pos.second + 1] == 'O') {
        ++count;
    }
    if (_map[_pos.first][_pos.second - 1] == 'O') {
        ++count;
    }
    if (_map[_pos.first - 1][_pos.second] == 'O') {
        ++count;
    }
    if (_map[_pos.first + 1][_pos.second] == 'O') {
        ++count;
    }
    if (count >= 1 && _isBomb == false) {
        _pos_bomb = _pos;
        _isBomb = true;
        // dropBomb(), function from Axel's ECS
    }
}

void Pnj::whereCanGo()
{
    std::vector<int> dir_possible;
    int i = 0;
    int j = 0;

    if (_isBomb == true) {
        if (_map[_pos.first][_pos.second + 1] == '.' && (_pos_bomb.first != _pos.first || _pos_bomb.second != _pos.second + 1)) {
            dir_possible.push_back(1);
            ++i;
            ++j;
        }
        if (_map[_pos.first][_pos.second - 1] == '.' && (_pos_bomb.first != _pos.first || _pos_bomb.second != _pos.second - 1)) {
            dir_possible.push_back(2);
            ++i;
            ++j;
        }
        if (_map[_pos.first - 1][_pos.second] == '.' && (_pos_bomb.first != _pos.first - 1 || _pos_bomb.second != _pos.second)) {
            dir_possible.push_back(3);
            ++i;
            ++j;
        }
        if (_map[_pos.first + 1][_pos.second] == '.' && (_pos_bomb.first != _pos.first + 1 || _pos_bomb.second != _pos.second)) {
            dir_possible.push_back(4);
            ++i;
            ++j;
        }
    }
    if (j == 0) {
        if (_map[_pos.first][_pos.second + 1] == '.') {
            dir_possible.push_back(1);
            ++i;
        }
        if (_map[_pos.first][_pos.second - 1] == '.') {
            dir_possible.push_back(2);
            ++i;
        }
        if (_map[_pos.first - 1][_pos.second] == '.') {
            dir_possible.push_back(3);
            ++i;
        }
        if (_map[_pos.first + 1][_pos.second] == '.') {
            dir_possible.push_back(4);
            ++i;
        }
    }

    _possible_mov.first = i;
    _possible_mov.second = dir_possible;
}

int Pnj::findMin()
{
    int temp = 4;

    for (auto &i : _possible_mov.second) {
        if (temp > i)
            temp = i;
    }
    return (temp);
}

int Pnj::findMax()
{
    int temp = 0;

    for (auto &i : _possible_mov.second) {
        if (temp < i)
            temp = i;
    }
    return (temp);
}

void Pnj::whereGoing()
{
    int temp = 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(1, _possible_mov.first);
    temp = distr(gen);
    _dir = _possible_mov.second.at(temp - 1);
    _inc = 0;
    if (_dir == (5 -_lastDir) && _possible_mov.first < 1) {
        _dir = 5 - _lastDir;
        _inc = 1;
    }
    if (_dir == 1) {
        _pos.second += 1;
    }
    else if (_dir == 2) {
        _pos.second -= 1;
    }
    else if (_dir == 3) {
        _pos.first -= 1;
    }
    else if (_dir == 4) {
        _pos.first += 1;
    }
    _lastDir = _dir;
}

int &Pnj::getDir()
{
    return _dir;
}

void Pnj::placePnj()
{
    int i = 1;
    int j = 1;
    std::ofstream save("../../Save/save.txt");

    _map[_pos.first][_pos.second] = _id;
        if (_dir == 1)
            _map[_pos.first][_pos.second - 1] = '.';
        if (_dir == 2)
            _map[_pos.first][_pos.second + 1] = '.';
        if (_dir == 3)
            _map[_pos.first + 1][_pos.second] = '.';
        if (_dir == 4)
            _map[_pos.first - 1][_pos.second] = '.';

    for (auto k : _map) {
        save << k << std::endl;
    }
}

void Pnj::globalLoop()
{
    time_t timer_loop = time(0);

    while(_alive) {
    // for (int i = 0; i < 100; i ++) {
        if (time(0) - timer_loop >= 1) {
            whereCanGo();
            whereGoing();
            placePnj();
            shouldDrop();
        }
    }
}

void Pnj::getPosid()
{
    int i = 0;
    int j = 0;
    std::cout << _id << std::endl;

    for (auto &ligne : _map) {
        ++j;
        i = 0;
        for (auto& caseboard : ligne) {
            ++i;
            if (caseboard == _id) {
                _pos.first = j - 1;
                _pos.second = i - 1;
            }
        }
    }
}