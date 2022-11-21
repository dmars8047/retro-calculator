#include <SDL.h>
#include <iostream>
#include "viewport.h"

const int DEFAULT_WIDTH = 392;
const int DEFAULT_HEIGHT = 40;

ViewPort::ViewPort(Texture *texture)
{
    width = DEFAULT_WIDTH;
    height = DEFAULT_HEIGHT;
    x = 0;
    y = 0;
    pTexture = texture;
}

ViewPort::~ViewPort()
{
    pTexture = NULL;
}

void ViewPort::Render(SDL_Renderer *renderer)
{
    pTexture->Render(renderer, x, y);
}

void ViewPort::Update(float deltaTime)
{

}