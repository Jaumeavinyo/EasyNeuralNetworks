#ifndef IMGUI_H
#define IMGUI_H

#include "Globals.h"
#include "Module.h"




class ModuleImGui : public Module {

public:

	ModuleImGui(Application* app, const char* moduleName, bool start_enabled = true);
	~ModuleImGui();

	bool Init(/*pugi::xml_node&*/);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);

	// Called before quitting
	bool CleanUp();

public:
	
	SDL_Event event;
	

	bool show_demo_window; 
	bool show_another_window; 

private:



};

#endif  IMGUI_H
