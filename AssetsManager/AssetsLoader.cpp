/*
** EPITECH PROJECT, 2022
** AssetsManager
** File description:
** AssetsLoader
*/

#include "AssetsLoader.hpp"
#include <iostream>

AssetManager* AssetManager::s_instance = nullptr;

AssetManager::AssetManager()
{
}

Texture2D AssetManager::getTexture(std::string id)
{
    if (textures.count(id) > 0)
        return textures[id];
}

Model AssetManager::getModel(std::string id)
{
    if (models.count(id) > 0)
        return models[id];
}

ModelAnimation *AssetManager::getModelAnim(std::string id)
{
    if (animations.count(id) > 0)
        return animations[id];
}

void AssetManager::loadModelAssets(std::string id, std::string path)
{
    if (models.count(id) <= 0) {
        Model model = LoadModel(path.c_str());
        if (model.materials == NULL)
            return;
        models[id] = model;
        std::cout << "model: [" << path << "] loaded!" << std::endl;
    }
}

void AssetManager::loadModelAnims(std::string id, std::string path, unsigned int anims)
{
    if (animations.count(id) <= 0) {
        ModelAnimation *anim = LoadModelAnimations(path.c_str(), &anims);
        animations[id] = anim;
        std::cout << "anim: [" << path << "] loaded!" << std::endl;
    }
}

void AssetManager::loadTextureAssets(std::string id, std::string path)
{
    if (textures.count(id) <= 0) {
        Texture2D texture = LoadTexture(path.c_str());
        if (texture.id <= 0)
            return;
        textures[id] = texture;
        std::cout << "texture: [" << path << "] loaded!" << std::endl;
    }
}