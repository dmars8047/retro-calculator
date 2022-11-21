#include <string>
#include <iostream>

#include "assetmanager.h"
#include "texture.h"

const std::string TEXTURE_FILE_PATH = "assets/textures/";
const std::string VIEWPORT_TEXTURE_FILE_NAME = "viewport.png";
const std::string NUMBER_TEXTURE_FILE_NAME = "numbers.png";
const std::string OPERATORS_TEXTURE_FILE_NAME = "operators.png";


AssetManager::AssetManager()
{
    pNumbersTexture = NULL;
    pOperatorTexture = NULL;
    pViewportTexture = NULL;
}

AssetManager::~AssetManager()
{
    delete pNumbersTexture;
    delete pOperatorTexture;
    delete pViewportTexture;
    pNumbersTexture = NULL;
    pOperatorTexture = NULL;
    pViewportTexture = NULL;
}

Texture *AssetManager::GetTexture(Uint32 identifier)
{
    switch (identifier)
    {
    case TEXTURESTORE_NUMBERS_TEXTURE:
        return pNumbersTexture;
    case TEXTURESTORE_OPERATORS_TEXTURE:
        return pOperatorTexture;
    case TEXTURESTORE_VIEWPORT_TEXTURE:
        return pViewportTexture;
    default:
        return nullptr;
    }
}

bool AssetManager::LoadTextures(SDL_Renderer *renderer)
{
    this->pViewportTexture = new Texture();

    // Load viewport texture
    if (!pViewportTexture->LoadFromFile(renderer, TEXTURE_FILE_PATH + VIEWPORT_TEXTURE_FILE_NAME))
    {
        std::cout << "Failed to load " << VIEWPORT_TEXTURE_FILE_NAME << " texture!" << std::endl;
        return false;
    }
    else
    {
        std::cout << "Loaded - " << VIEWPORT_TEXTURE_FILE_NAME << std::endl;
    }

    this->pNumbersTexture = new Texture();

    // Load numbers texture
    if (!pNumbersTexture->LoadFromFile(renderer, TEXTURE_FILE_PATH + NUMBER_TEXTURE_FILE_NAME))
    {
        std::cout << "Failed to load arrow " << NUMBER_TEXTURE_FILE_NAME << " texture!" << std::endl;
        return false;
    }
    else
    {
        std::cout << "Loaded - " << NUMBER_TEXTURE_FILE_NAME << std::endl;
    }

    this->pOperatorTexture = new Texture();

    // Load numbers texture
    if (!pOperatorTexture->LoadFromFile(renderer, TEXTURE_FILE_PATH + OPERATORS_TEXTURE_FILE_NAME))
    {
        std::cout << "Failed to load  " << OPERATORS_TEXTURE_FILE_NAME << "  texture!" << std::endl;
        return false;
    }
    else
    {
        std::cout << "Loaded - " << OPERATORS_TEXTURE_FILE_NAME << std::endl;
    }

    return true;
}