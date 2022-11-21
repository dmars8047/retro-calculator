#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <string>

// Texture wrapper class
class Texture
{
public:
	// Initializes variables
	Texture();

	// Deallocates memory
	virtual ~Texture();

	// Loads image at specified path
	bool LoadFromFile(SDL_Renderer *renderer, std::string path);

#if defined(SDL_TTF_MAJOR_VERSION)
	// Creates image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
#endif

	// Set color modulation
	void SetColor(Uint8 red, Uint8 green, Uint8 blue);

	// Set blending
	void SetBlendMode(SDL_BlendMode blending);

	// Set alpha modulation
	void SetAlpha(Uint8 alpha);

	// Renders texture at given point
	void Render(SDL_Renderer *renderer, int x, int y, SDL_Rect *clip = NULL, double angle = 0.0, SDL_FPoint *center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	// Renders texture at a given floating point using sub pixel rendering.
	void RenderFloat(SDL_Renderer *renderer, float x, float y, SDL_Rect *clip, double angle, SDL_FPoint *center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	// Gets image dimensions
	int GetTextureWidth();
	int GetTextureHeight();

private:
	// The actual hardware texture
	SDL_Texture *pTexture;
	// Image dimensions
	int mWidth;
	int mHeight;
	// Deallocates texture
	void free();
};

#endif
