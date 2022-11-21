#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>

#include "assetmanager.h"
#include "viewport.h"

const int MAIN_WINDOW_WIDTH = 400;
const int MAIN_WINDOW_HEIGHT = 600;
const std::string APP_NAME = "Retro Calculator";

// Background colors
const int BACKGROUND_RED = 255;
const int BACKGROUND_GREEN = 251;
const int BACKGROUND_BLUE = 247;
const int BACKGROUND_ALPHA = 255;

// The window we'll be rendering to
SDL_Window *gMainWindow = NULL;

// The window renderer
SDL_Renderer *gRenderer = NULL;

// A store for textures
AssetManager *gAssetManager = NULL;

bool initSDL()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    // Set texture filtering to linear
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2"))
    {
        printf("Warning: Best texture filtering not enabled!");
    }
    else if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
        printf("Warning: Linear texture filtering not enabled!");
    }

    gMainWindow = SDL_CreateWindow(APP_NAME.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    if (gMainWindow == NULL)
    {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    // Create vsynced renderer for window
    gRenderer = SDL_CreateRenderer(gMainWindow, -1, SDL_RENDERER_ACCELERATED);

    if (gRenderer == NULL)
    {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    // Initialize renderer color
    SDL_SetRenderDrawColor(gRenderer, BACKGROUND_RED, BACKGROUND_GREEN, BACKGROUND_BLUE, BACKGROUND_ALPHA);

    // Initialize PNG loading
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }

    return true;
}

bool loadMedia()
{
    gAssetManager = new AssetManager();

    return gAssetManager->LoadTextures(gRenderer);
}

bool close(int returnCode)
{
    // Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gMainWindow);

    // Clean up texture store
    delete gAssetManager;

    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();

    return returnCode;
}

int main()
{
    if (!initSDL())
    {
        std::cout << "Failed to initialize calculator window!" << std::endl;
        return close(1);
    }

    // Load media
    if (!loadMedia())
    {
        std::cout << "Failed to load calculator media!" << std::endl;
        return close(1);
    }

    // Initialize loop
    bool quit = false;

    // Event handler
    SDL_Event e;

    ViewPort viewport = ViewPort(gAssetManager->GetTexture(TEXTURESTORE_VIEWPORT_TEXTURE));

    while (!quit)
    {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0)
        {
            // User requests quit
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    quit = true;
                    break;
                default:
                    break;
                }
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(gRenderer, BACKGROUND_RED, BACKGROUND_GREEN, BACKGROUND_BLUE, BACKGROUND_ALPHA);
        SDL_RenderClear(gRenderer);

        viewport.Render(gRenderer);

        // Update screen
        SDL_RenderPresent(gRenderer);
    }

    return close(0);
}