#ifndef SDL_MANAGER_H_
#define SDL_MANAGER_H_

#include "SDL.h"
#include "..\EasyNeuralNetworksProject\lib\SDL2\include\SDL_image.h"//allows to load images
#include "p2List.h"


class SDLManager
{

public:
	SDLManager();
	~SDLManager();



	SDL_Texture* const loadTexture(const char* filePath, SDL_Renderer* renderer);
	SDL_Texture* const loadSurface(SDL_Surface* surface, SDL_Renderer* renderer);


	p2List<SDL_Texture*> textures;
};




#endif