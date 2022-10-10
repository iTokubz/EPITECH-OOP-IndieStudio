/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-thomas.weinstein
** File description:
** Settings
*/

#include <iostream>
#include "raylib.h"

#ifndef SETTINGS_HPP_
#define SETTINGS_HPP_

struct Settings {
    std::size_t nbrBombs;
    int _keyBomb;
    int _keyUp;
    int _keyDown;
    int _keyLeft;
    int _keyRight;
    bool _AI;
    Color _color;
};

#endif /* !SETTINGS_HPP_ */
