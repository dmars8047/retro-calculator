#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>

const int MAIN_WINDOW_WIDTH = 400;
const int MAIN_WINDOW_HEIGHT = 600;
const std::string APP_NAME = "Retro Calculator";

// Background colors
const int BACKGROUND_RED = 255;
const int BACKGROUND_GREEN = 251;
const int BACKGROUND_BLUE = 247;
const int BACKGROUND_ALPHA = 255;

// The window we'll be rendering to
SDL_Window *mainWindow = NULL;

// The window renderer
SDL_Renderer *renderer = NULL;

bool initSDL()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
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

    mainWindow = SDL_CreateWindow(APP_NAME.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    if (mainWindow == NULL)
    {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    // Create vsynced renderer for window
    renderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == NULL)
    {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    // Initialize renderer color
    SDL_SetRenderDrawColor(renderer, BACKGROUND_RED, BACKGROUND_GREEN, BACKGROUND_BLUE, BACKGROUND_ALPHA);

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
    return true;
}

bool close(int returnCode)
{
    // Destroy window
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(mainWindow);

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
        SDL_SetRenderDrawColor(renderer, BACKGROUND_RED, BACKGROUND_GREEN, BACKGROUND_BLUE, BACKGROUND_ALPHA);
        SDL_RenderClear(renderer);

        // Update screen
        SDL_RenderPresent(renderer);
    }

    return close(0);
}