/*
** EPITECH PROJECT, 2022
** EntityComponentSystem
** File description:
** ECS
*/

#ifndef ECS_HPP_
#define ECS_HPP_

class Entity;
class Component;

#include <array>
#include <bitset>
#include <iostream>

using ComponentTypeID = std::size_t;

inline ComponentTypeID getComponentID()
{
    static ComponentTypeID lastID = 0u;
    return lastID++;
}

template <typename T>
inline ComponentTypeID getComponentTypeID() noexcept
{
    static ComponentTypeID typeID = getComponentID();
    return typeID;
}

constexpr std::size_t MAX_ENTITIES = 400;
constexpr std::size_t MAX_COMPONENTS = 100;

using ComponentBitset = std::bitset<MAX_COMPONENTS>;
using ComponentList = std::array<Component *, MAX_COMPONENTS>;

#endif /* !ECS_HPP_ */
