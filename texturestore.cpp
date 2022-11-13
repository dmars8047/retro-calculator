#include <SDL_image.h>
#include <string>

#include "texturestore.h"

const std::string VIEWPORT_TEXTURE_FILE_NAME = "viewport.png";
const std::string NUMBER_TEXTURE_FILE_NAME = "numbers.png";
const std::string OPERATORS_TEXTURE_FILE_NAME = "operators.png";

#define TEXTURESTORE_VIEWPORT_TEXTURE   0x01u
#define TEXTURESTORE_NUMBERS_TEXTURE   0x02u
#define TEXTURESTORE_OPERATORS_TEXTURE   0x03u

TextureStore::TextureStore() {
    pNumbersTexture = NULL;
    pOperatorTexture = NULL;
    pViewportTexture = NULL;
}

TextureStore::~TextureStore() {
    delete pNumbersTexture;
    delete pOperatorTexture;
    delete pViewportTexture;
    pNumbersTexture = NULL;
    pOperatorTexture = NULL;
    pViewportTexture = NULL;
}

SDL_Texture* TextureStore::GetTexture(Uint32 identifier) {
    switch(identifier) {
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