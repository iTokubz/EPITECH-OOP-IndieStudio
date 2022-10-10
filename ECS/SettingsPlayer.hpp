/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-thomas.weinstein
** File description:
** SettingsPlayer
*/

#ifndef SETTINGSPLAYER_HPP_
#define SETTINGSPLAYER_HPP_

#include "../GameEngine/Settings.hpp"
#include "MapComponent.hpp"
#include "MapController.hpp"
// #include "KeyboardControler.hpp"
#include "ECS.hpp"


class SettingsPlayer : public Component {
    public:
        SettingsPlayer() = default;
        ~SettingsPlayer() = default;
        void init() override
        {
            numberOfBombs = 2;
            isAlive = true;
        }

        std::size_t getBombsNbr()
        {
            return numberOfBombs;
        }

        bool &getIsAlive()
        {
            return isAlive;
        }
        void setMap(float x, float z)
        {
            int destruction_x = x/2 + 7.0f;
            int destruction_z = z/2 + 6.0f;
            if(control->map->getMap()[destruction_z][destruction_x+1] == 'O')
                control->map->getMap()[destruction_z][destruction_x+1] = '.';
            if(control->map->getMap()[destruction_z+1][destruction_x] == 'O')
                control->map->getMap()[destruction_z+1][destruction_x] = '.';
            if(control->map->getMap()[destruction_z][destruction_x-1] == 'O')
                control->map->getMap()[destruction_z][destruction_x-1] = '.';
            if(control->map->getMap()[destruction_z-1][destruction_x] == 'O')
                control->map->getMap()[destruction_z-1][destruction_x] = '.';
        }
        void update() override
        {
            control = &_entity->getComponent<MapController>();
        }

    private:
        std::size_t numberOfBombs;
        MapController *control;
        MapComponent *_map;
        bool wallPass;
        bool isAlive;
        float speed;
        float rangeBomb;
        Settings _set;
        std::vector<std::string> test;
};

#endif /* !SETTINGSPLAYER_HPP_ */
