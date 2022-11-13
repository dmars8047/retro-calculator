#ifndef CALC_TEXTURE_STORE
#define CALC_TEXTURE_STORE

#include <SDL_image.h>

class TextureStore
{
    private:
        SDL_Texture* pViewportTexture;
        SDL_Texture* pNumbersTexture;
        SDL_Texture* pOperatorTexture;
    public:
        TextureStore();
        ~TextureStore();
        SDL_Texture* GetTexture(Uint32 identifier);
        bool LoadTextures();
};

#endif