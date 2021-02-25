#include "Globals.h"
#include "Module.h"


class Application
{
public:
	//modules here
	Module* window;
	
private:

						
	float dt;	//delta time

						

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