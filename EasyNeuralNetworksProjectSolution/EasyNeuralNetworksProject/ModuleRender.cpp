#include "glad/glad.h"
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
	
	// clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	glViewport(0, 0, (int)SCREEN_WIDTH, (int)SCREEN_HEIGHT);
	//setBackgroundColor(1, 1, 0, 1);
	glClearColor(background.r, background.g, background.b, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	
	SDL_SetRenderDrawColor(renderer, background.r, background.g, background.g, background.a);//SET COLOR FOR RENDERING
	//SDL_RenderPresent(renderer);//UPDATE SCREEN WITH NEW RENDERING DONE
	SDL_GL_SwapWindow(App->window->window);
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

bool ModuleRender::Blit(SDL_Texture* texture, int x, int y, const SDL_Rect* section, SDL_RendererFlip flip, bool use_camera, float scale_, float speed, double angle, int pivot_x, int pivot_y) const {
	
	bool ret = true;

	SDL_Rect rect;

	if (use_camera) {
		rect.x = (int)(camera.x * speed) + x;
		rect.y = (int)(camera.y * speed) + y;
	}
	else {
		rect.x = x;
		rect.y = y;
	}

	if (section != NULL) {
		rect.w = section->w;
		rect.h = section->h;

	}
	else {
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	}

	rect.w *= scale_;
	rect.h *= scale_;

	SDL_Point* p = NULL;
	SDL_Point pivot;

	if (pivot_x != INT_MAX && pivot_y != INT_MAX)
	{
		pivot.x = pivot_x;
		pivot.y = pivot_y;
		p = &pivot;
	}

	if (SDL_RenderCopyEx(renderer, texture, section, &rect, angle, p, flip) != 0)
	{
		std::cout << "\n Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError();
		ret = false;
	}

	return ret;


}