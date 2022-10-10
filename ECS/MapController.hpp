/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-thomas.weinstein
** File description:
** MapController
*/

#ifndef MAPCONTROLLER_HPP_
#define MAPCONTROLLER_HPP_

#include "ECS.hpp"
#include "MapComponent.hpp"

class MapController : public Component {
    public:
        MapController(Entity &MapEntity) : _mapEntity(MapEntity) {}
        ~MapController() = default;
        MapComponent *map;
        void init() override
        {
            map = &_mapEntity.getComponent<MapComponent>();
        }

        void draw() override
        {
            // std::cout << map->getMap()[0] << std::endl;
        }

    private:
        Entity &_mapEntity;
        std::vector<std::string> _map;
};

#endif /* !MAPCONTROLLER_HPP_ */
