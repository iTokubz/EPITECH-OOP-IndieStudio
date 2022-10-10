/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-thomas.weinstein
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include "../GameEngine/Settings.hpp"
#include <vector>

class Core {
    public:
        Core();
        ~Core();
        void startMenu();
        void startGame(std::vector<struct Settings> settings);
    private:
};

#endif /* !CORE_HPP_ */
