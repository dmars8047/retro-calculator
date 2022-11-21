#include <string>
#include <iostream>
#include <vector>
#include <filesystem>

#include "assetmanager.h"
#include "texture.h"

const std::string TEXTURE_FILE_PATH = "assets/textures/";

AssetManager::AssetManager()
{
    pTextures = new std::vector<Texture *>();
}

AssetManager::~AssetManager()
{
    for(int i = 0; i < pTextures->size(); i++)
    {
        delete pTextures->at(i);
    }

    delete pTextures;
}

Texture *AssetManager::GetTexture(std::string identifier)
{
    for (int i = 0; i < pTextures->size(); i++)
    {
        Texture *texture = pTextures->at(i);
        if (identifier == *texture->GetId())
        {
            return texture;
        }
    }

    return nullptr;
}

bool AssetManager::LoadTextures(SDL_Renderer *renderer)
{
    for (const std::filesystem::directory_entry &entry : std::filesystem::directory_iterator(TEXTURE_FILE_PATH))
    {
        if (entry.path().extension() == ".png")
        {
            std::string fileName = entry.path().filename();

            Texture *texture = new Texture(fileName.substr(0, fileName.find_last_of(".")));

            if (!texture->LoadFromFile(renderer, TEXTURE_FILE_PATH + fileName))
            {
                std::cout << "Failed to load " << fileName << " texture!" << std::endl;
                return false;
            }
            else
            {
                pTextures->push_back(texture);
                std::cout << "Loaded - " << fileName << " texture!" << std::endl;
            }
        }
    }

    return true;
}