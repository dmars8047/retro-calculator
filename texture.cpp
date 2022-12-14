// #include <SDL2/SDL_image.h>
#include <SDL_image.h>
#include <iostream>

#include "texture.h"

Texture::Texture(std::string id)
{
	// Initialize
	mId = id;
	pTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

Texture::~Texture()
{
	// Deallocate
	free();
}

bool Texture::LoadFromFile(SDL_Renderer *renderer, std::string path)
{
	// Get rid of preexisting texture
	free();

	// The final texture
	SDL_Texture *newTexture = NULL;

	// Load image at specified path
	SDL_Surface *loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == NULL)
	{
		std::cout << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << std::endl;
	}
	else
	{
		// Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		// Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			// Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		// Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	// Return success
	pTexture = newTexture;
	return pTexture != NULL;
}

#if defined(SDL_TTF_MAJOR_VERSION)
bool Texture::LoadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	// Get rid of preexisting texture
	free();

	// Render text surface
	SDL_Surface *textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface != NULL)
	{
		// Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			// Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		// Get rid of old surface
		SDL_FreeSurface(textSurface);
	}
	else
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}

	// Return success
	return mTexture != NULL;
}
#endif

void Texture::free()
{
	// Free texture if it exists
	if (pTexture != NULL)
	{
		std::cout << "Freeing texture - " << mId << std::endl;

		SDL_DestroyTexture(pTexture);
		pTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void Texture::SetColor(Uint8 red, Uint8 green, Uint8 blue)
{
	// Modulate texture rgb
	SDL_SetTextureColorMod(pTexture, red, green, blue);
}

void Texture::SetBlendMode(SDL_BlendMode blending)
{
	// Set blending function
	SDL_SetTextureBlendMode(pTexture, blending);
}

void Texture::SetAlpha(Uint8 alpha)
{
	// Modulate texture alpha
	SDL_SetTextureAlphaMod(pTexture, alpha);
}

void Texture::Render(SDL_Renderer *renderer, int x, int y, SDL_Rect *clip, double angle, SDL_FPoint *center, SDL_RendererFlip flip)
{
	// Set rendering space and render to screen
	SDL_FRect renderQuad = {(float)x, (float)y, (float)mWidth, (float)mHeight};

	// Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	// Render to screen
	SDL_RenderCopyExF(renderer, pTexture, clip, &renderQuad, angle, center, flip);
}

void Texture::RenderFloat(SDL_Renderer *renderer, float x, float y, SDL_Rect *clip, double angle, SDL_FPoint *center, SDL_RendererFlip flip)
{
	// Set rendering space and render to screen
	SDL_FRect renderQuad = {x, y, (float)mWidth, (float)mHeight};

	// Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	// Render to screen
	SDL_RenderCopyExF(renderer, pTexture, clip, &renderQuad, angle, center, flip);
}

int Texture::GetTextureWidth()
{
	return mWidth;
}

int Texture::GetTextureHeight()
{
	return mHeight;
}

std::string *Texture::GetId()
{
	return &mId;
}