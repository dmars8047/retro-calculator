#ifndef CALC_TEXTURE_STORE
#define CALC_TEXTURE_STORE

#include "texture.h"

#define TEXTURESTORE_VIEWPORT_TEXTURE 0x01u
#define TEXTURESTORE_NUMBERS_TEXTURE 0x02u
#define TEXTURESTORE_OPERATORS_TEXTURE 0x03u

class AssetManager
{
private:
    Texture *pViewportTexture;
    Texture *pNumbersTexture;
    Texture *pOperatorTexture;

public:
    AssetManager();
    ~AssetManager();
    Texture *GetTexture(Uint32 identifier);
    bool LoadTextures(SDL_Renderer *renderer);
};

#endif