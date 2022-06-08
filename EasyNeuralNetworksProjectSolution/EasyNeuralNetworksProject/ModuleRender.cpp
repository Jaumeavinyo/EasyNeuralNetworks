#include "ModuleRender.h"
#include "App.h"


//############  CONSTRUCTORS ############


ModuleRender::ModuleRender(Application* app, const char* moduleName, bool start_enabled) : Module(app, start_enabled, moduleName){



}

ModuleRender::~ModuleRender() {

}


//############  MAIN APP FUNCTIONS ############


bool ModuleRender::Init() {
	
	printf("ModuleRender Init()\n");

	bool ret = true;

	uint32 flags = SDL_RENDERER_ACCELERATED;

	renderer = SDL_CreateRenderer(App->window->window, -1, flags);

	if (renderer == NULL) {

		printf(" ---> Error creating renderer SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else {
		camera.h = App->window->screen_surface->h;
		camera.w = App->window->screen_surface->w;
		camera.x = 100;
		camera.y = 200;
	}

	return ret;

}

bool ModuleRender::Start() {
	
	bool ret = true;

	printf("ModuleRender Start()\n");

	SDL_RenderGetViewport(renderer, &viewport); //GET THE DRAWING AREA FOR THE CURRENT TARGET
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);//SET DEVICE INDEPENDENT RESOLUTION FOR RENDERING. (IN THIS CASE RENDERING RESOLUTION IS OUR SCREEN RESOLUTION)

	return ret;

}

update_status  ModuleRender::PreUpdate(float dt) {

	update_status ret = update_status::UPDATE_CONTINUE;

	SDL_RenderClear(renderer);//CLEAR PREV FRAME SCREEN

	return ret;
}

update_status  ModuleRender::Update(float dt) {

	update_status ret = update_status::UPDATE_CONTINUE;

	return ret;
}

update_status  ModuleRender::PostUpdate(float dt) {

	update_status ret = update_status::UPDATE_CONTINUE;

	SDL_SetRenderDrawColor(renderer, background.r, background.g, background.g, background.a);//SET COLOR FOR RENDERING
	//SDL_RenderPresent(renderer);//UPDATE SCREEN WITH NEW RENDERING DONE

	return ret;
}


bool ModuleRender::CleanUp() {

	bool ret = true;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(App->window->window);
	SDL_Quit();
	return ret;

}

//############  UTILITY FUNCTIONS ############


void ModuleRender::setBackgroundColor(int r, int g, int b, int a) {

	background.r = r;
	background.g = g;
	background.b = b;
	background.a = a;

}

void ModuleRender::ScreenToWorld(int* x, int* y) const
{
	int scale = App->window->GetScale();

	x = (x - camera.x / scale);
	y = (y - camera.y / scale);
}

iPoint ModuleRender::ScreenToWorld(int x, int y) const
{
	iPoint ret;
	int scale = App->window->GetScale();

	ret.x = (x - camera.x / scale);
	ret.y = (y - camera.y / scale);

	return ret;
}