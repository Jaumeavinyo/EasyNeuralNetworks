#include "SDLManager.h"

#include "Globals.h"



SDLManager::SDLManager()
{
	printf(" SDLManager Created \n ");
}

SDLManager::~SDLManager()
{
}

SDL_Texture* const SDLManager::load(const char* filePath, SDL_Renderer* renderer) {

	SDL_Texture* texture = NULL;
	SDL_Surface* surface = IMG_Load(filePath);

	if (surface == NULL)
	{
		printf("\n Could not load surface with path: %s. IMG_Load: %s", filePath, IMG_GetError());
	}
	else
	{
		texture = loadSurface(surface, renderer);
		SDL_FreeSurface(surface);
	}

	return texture;
}

// Translate a surface into a texture
SDL_Texture* const SDLManager::loadSurface(SDL_Surface* surface, SDL_Renderer* renderer)
{
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == NULL)
		printf("Unable to create texture from surface! SDL Error: %s\n", SDL_GetError());
	else
		textures.add(texture);

	return texture;
}