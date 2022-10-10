// /*
// ** EPITECH PROJECT, 2022
// ** Game_test
// ** File description:
// ** ColliderComponent
// */

// #ifndef COLLIDERCOMPONENT_HPP_
// #define COLLIDERCOMPONENT_HPP_

// #include <string>
// #include <SDL2/SDL.h>
// #include "Components.hpp"
// // #include "../Games/SolarFox/SolarFox.hpp"

// class ColliderComponent : public Component {
//     public:
//         SDL_Rect collider;
//         std::string tag;

//         ColliderComponent(std::string t)
//         {
//             tag = t;
//         }

//         void init() override
//         {
//             if (!_entity->hasComponent<TransformComponent>()) {
//                 _entity->addComponent<TransformComponent>();
//             }
//             transform = &_entity->getComponent<TransformComponent>();

//             SolarFox::_colliders.push_back(this);
//         }

//         void update(IGraphicModules *Gfx) override
//         {
//             collider.x = static_cast<int>(transform->position.x);
//             collider.y = static_cast<int>(transform->position.y);
//             collider.w = transform->width * transform->scale;
//             collider.h = transform->height * transform->scale;
//         }
//     private:
//         TransformComponent *transform;
// };

// #endif /* !COLLIDERCOMPONENT_HPP_ */
