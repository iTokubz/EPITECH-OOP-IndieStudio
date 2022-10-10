/*
** EPITECH PROJECT, 2022
** AssetsManager
** File description:
** AssetsLoader
*/

#ifndef ASSETSLOADER_HPP_
#define ASSETSLOADER_HPP_

#include <map>
#include "raylib.h"
#include <string>

class AssetManager {

    public:
        AssetManager();
        ~AssetManager() = default;
        void clean();
        Texture2D getTexture(std::string id);
        Model getModel(std::string id);
        ModelAnimation *getModelAnim(std::string id);
        void loadModelAssets(std::string id, std::string path);
        void loadTextureAssets(std::string id, std::string path);
        void loadModelAnims(std::string id, std::string path, unsigned int animsCount);

        inline static AssetManager& get()
        {
            if(s_instance == nullptr) {
                s_instance = new AssetManager();
            }
            return *s_instance;
        }
    private:
        static AssetManager* s_instance;
        std::map<std::string, Texture2D> textures;
        std::map<std::string, Model> models;
        std::map<std::string, ModelAnimation *> animations;
};

#endif /* !ASSETSLOADER_HPP_ */
