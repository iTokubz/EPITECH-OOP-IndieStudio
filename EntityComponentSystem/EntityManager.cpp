/*
** EPITECH PROJECT, 2022
** EntityComponentSystem
** File description:
** EntityManager
*/

#include "EntityManager.hpp"
#include <algorithm>
#include <iostream>
#include <memory>
#include "Entity.hpp"

void EntityManager::draw()
{

     for(auto& entity : entities)
        entity->draw();
}

void EntityManager::update()
{
     for(auto& entity : entities)
        entity->update();
}

void EntityManager::addEntity(Entity* entity)
{
    std::unique_ptr<Entity> uniquePtr{ entity };
    entities.emplace_back(std::move(uniquePtr));
}

Entity* EntityManager::cloneEntity(Entity* entity)
{
    return nullptr;
}

