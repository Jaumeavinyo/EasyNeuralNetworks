#ifndef MODULE_WINDOW_H_
#define MODULE_WINDOW_H_

#include "Globals.h"
#include "Module.h"
#include <SDL.h>

class ModuleWindow : public Module
{
public:

	ModuleWindow(Application* app,const char* moduleName, bool start_enabled = true);

	// Destructor
	virtual ~ModuleWindow();

	bool Init();
	bool CleanUp();

	void SetTitle(const char* title);

	void SetFullscreen(bool active);

	void SetBorderless(bool active);

	void SetResizable(bool active);

	void SetWindowSize(int width, int height);

public:

	const char* window_title = "Easy Neural Networks";

	SDL_Window*			window = NULL; //The window we'll be rendering to	
	SDL_Surface*		screen_surface;//The surface contained by the window

};

#endif MODULE_WINDOW_H_