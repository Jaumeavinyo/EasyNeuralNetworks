#include "ModuleRender.h"


//############  CONSTRUCTORS ############


ModuleRender::ModuleRender(Application* app, const char* moduleName, bool start_enabled) : Module(app, start_enabled, moduleName){

	int a = 1;

}

ModuleRender::~ModuleRender() {

}


//############  MAIN APP FUNCTIONS ############


bool ModuleRender::Init() {
	
	printf("ModuleRender Init()");

	bool ret = true;

	uint32 flags = SDL_RENDERER_ACCELERATED;
	
	if (VSYNC) {
		flags |= SDL_RENDERER_PRESENTVSYNC;
		printf(" --- > Using Vsync");
	}

	return ret;

}

bool ModuleRender::Start() {

	bool ret = true;

	return ret;

}

update_status  ModuleRender::PreUpdate(float dt) {

	update_status ret = update_status::UPDATE_CONTINUE;
	return ret;
}

update_status  ModuleRender::Update(float dt) {

	update_status ret = update_status::UPDATE_CONTINUE;
	return ret;
}

update_status  ModuleRender::PostUpdate(float dt) {

	update_status ret = update_status::UPDATE_CONTINUE;
	return ret;
}


bool ModuleRender::CleanUp() {

	bool ret = true;
	return ret;

}

//############  UTILITY FUNCTIONS ############


void ModuleRender::setBackgroundColor(int r, int g, int b, int a) {

	background.r = r;
	background.g = g;
	background.b = b;
	background.a = a;

}
