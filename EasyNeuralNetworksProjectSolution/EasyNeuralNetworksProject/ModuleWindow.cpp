#include "ModuleWindow.h"
#include "App.h"
#include "lib\ImGUI\backends\imgui_impl_opengl3.h"
#include "glad/glad.h"
//############  CONSTRUCTORS ############


ModuleWindow::ModuleWindow(Application* app,const char* moduleName, bool start_enabled) : Module(app, start_enabled,moduleName) {

	window = NULL;
	screen_surface = NULL;

}

ModuleWindow::~ModuleWindow() {

}


//############  MAIN APP FUNCTIONS ############


bool ModuleWindow::Init() {
	
	printf(" ModuleWindow Init()\n ");

	bool ret = true;

	int width = SCREEN_WIDTH * SCREEN_SIZE;
	int height = SCREEN_HEIGHT * SCREEN_SIZE;
	scale = SCREEN_SIZE;
	Uint32 flags = SDL_WINDOW_SHOWN;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0) //imgui main.cpp uses it
	{
		printf(" ---> SDL_Init Error: %s\n", SDL_GetError());
		ret = false;
	}

	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	// Setup window
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);  //imgui main.cpp uses it
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);   //imgui main.cpp uses it
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);  //imgui main.cpp uses it
	SDL_GL_SetAttribute(
		SDL_GL_CONTEXT_PROFILE_MASK,
		SDL_GL_CONTEXT_PROFILE_CORE
	);
	if (SDL_WIN_ALLOW_HIGHDPI == true) {//imgui main.cpp uses it
		flags |= SDL_WINDOW_ALLOW_HIGHDPI;
	}

	if (SDL_WIN_OPENGL == true) { //imgui main.cpp uses it
		flags |= SDL_WINDOW_OPENGL;
	}

	if (WIN_FULLSCREEN == true) {
		flags |= SDL_WINDOW_FULLSCREEN;
	}

	if (WIN_RESIZABLE == true) {
		flags |= SDL_WINDOW_RESIZABLE;//imgui main.cpp uses it
	}

	if (WIN_BORDERLESS == true) {
		flags |= SDL_WINDOW_BORDERLESS;
	}

	if (WIN_FULLSCREEN_DESKTOP == true) {
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	}
	if (WIN_DOUBLE_BUFFERING == true) {//imgui main.cpp uses it
		//flags |= GL_DOUBLEBUFFER;// glew.h stuff
	}
	if (VSYNC == true) {
		SDL_GL_SetSwapInterval(1); //imgui main.cpp uses it
	}

	window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

	gl_context = SDL_GL_CreateContext(window);  
	SDL_GL_MakeCurrent(window, gl_context);     
	

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

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		std::cerr << "[ERROR] Couldn't initialize glad" << std::endl;
	}
	else
	{
		std::cout << "[INFO] glad initialized\n";
	}

	/* Drag and drop events can be placed here from SDL_events.h */


	return ret;
}

bool ModuleWindow::CleanUp() {

	SDL_GL_DeleteContext(gl_context);
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

