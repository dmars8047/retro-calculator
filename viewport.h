#ifndef CALC_VIEWPORT
#define CALC_VIEWPORT

#include <string>
#include <SDL.h>

#include "texture.h"

class ViewPort
{
private:
    int height;
    int width;
    int x;
    int y;
    Texture *pTexture;

public:
    ViewPort(Texture *texture);
    ~ViewPort();
    void Render(SDL_Renderer *renderer);
    void Update(float deltaTime);
};

#endif