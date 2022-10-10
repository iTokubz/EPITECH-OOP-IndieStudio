/*
** EPITECH PROJECT, 2022
** EntityComponentSystem
** File description:
** Component
*/

#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

class Entity;

class Component {
    public:
        Component() = default;
        ~Component() = default;
        Entity *entity;
        virtual bool init(){return true;}
        virtual void draw(){}
        virtual void update(){}
};

#endif /* !COMPONENT_HPP_ */
