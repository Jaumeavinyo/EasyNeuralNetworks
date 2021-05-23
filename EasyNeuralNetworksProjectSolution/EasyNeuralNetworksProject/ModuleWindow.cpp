#include "ModuleWindow.h"
#include "App.h"

//############  CONSTRUCTORS ############


ModuleWindow::ModuleWindow(Application* app,const char* moduleName, bool start_enabled) : Module(app, start_enabled,moduleName) {

	window = NULL;
	screen_surface = NULL;

}

ModuleWindow::~ModuleWindow() {

}


//############  MAIN APP FUNCTIONS ############


bool ModuleWindow::Init() {
	
	printf(" ModuleWindow Init() ");

	bool ret = true;

	int width = SCREEN_WIDTH * SCREEN_SIZE;
	int height = SCREEN_HEIGHT * SCREEN_SIZE;
	Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;

	//Use OpenGL 2.1
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	if (WIN_FULLSCREEN == true)
	{
		flags |= SDL_WINDOW_FULLSCREEN;
	}

	if (WIN_RESIZABLE == true)
	{
		flags |= SDL_WINDOW_RESIZABLE;
	}

	if (WIN_BORDERLESS == true)
	{
		flags |= SDL_WINDOW_BORDERLESS;
	}

	if (WIN_FULLSCREEN_DESKTOP == true)
	{
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	}
	/*if (WIN_DOUBLE_BUFFERING == true) {
		flags |= GL_DOUBLEBUFFER;// glew.h stuff
	}*/

	window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

	if (window == NULL)
	{
		
		printf(" ---> Window could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		//Get window surface
		screen_surface = SDL_GetWindowSurface(window);
	}

	/* Drag and drop events can be placed here from SDL_events.h */


	return ret;
}

bool ModuleWindow::CleanUp() {

	if (window != NULL) {
		SDL_DestroyWindow(window);
	}

	SDL_Quit();//cleans other sdl subsystems

	return true;
}


//############  UTILITY FUNCTIONS ############


void ModuleWindow::SetTitle(const char* title)
{
	SDL_SetWindowTitle(window, title);
}

void ModuleWindow::SetFullscreen(bool active) {
	if (active)
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	else
		SDL_SetWindowFullscreen(window, SDL_WINDOW_MINIMIZED);
}

void ModuleWindow::SetBorderless(bool active) {
	if (active)
		SDL_SetWindowBordered(window, SDL_FALSE);
	else
		SDL_SetWindowBordered(window, SDL_TRUE);
}

void ModuleWindow::SetResizable(bool active) {
	if (active)
		SDL_SetWindowResizable(window, SDL_TRUE);
	else
		SDL_SetWindowResizable(window, SDL_FALSE);
}

void ModuleWindow::SetWindowSize(int width, int height) {
	SDL_SetWindowSize(window, width, height);
}

float ModuleWindow::GetScale() {
	return scale;
}

void ModuleWindow::SetScale(float newScale){
	scale = newScale;
}