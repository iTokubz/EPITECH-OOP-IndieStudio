/*
** EPITECH PROJECT, 2022
** EntityComponentSystem
** File description:
** EntityManager
*/

#ifndef ENTITYMANAGER_HPP_
#define ENTITYMANAGER_HPP_

#include <vector>
#include <memory>

class Entity;

class EntityManager {
    public:
        EntityManager() = default;
        virtual ~EntityManager() = default;

        void draw();
        void update();
        void refresh();

        void addEntity(Entity *player);
        void eraseEntity(Entity *player);
        Entity* cloneEntity(Entity *player);

    private:
        std::vector<std::unique_ptr<Entity>> entities;
};

#endif /* !ENTITYMANAGER_HPP_ */
