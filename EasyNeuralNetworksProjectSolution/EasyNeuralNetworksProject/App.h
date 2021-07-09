#include "Globals.h"
#include "Module.h"

#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleImGui.h"
#include "ModuleScene.h"



class Application{

public:
	//modules here
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput*  input;
	ModuleImGui* imgui;
	ModuleScene* scene;

private:
	
						
	float dt = 0.1f;	//delta time need to be done and added to update functions

						

	p2List<Module*> p_list_modules;			//All Application modules inside

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	const char* GetAppName() const;
	void SetAppName(const char* name);
	bool CleanUp();

private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();

	
	std::string app_name;
	std::string organization_name;

};

extern Application* App;