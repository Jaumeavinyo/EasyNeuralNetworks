#include "p2List.h"

class App
{
public:
	//modules here

	
private:

						
	float   dt;	//delta time

						

	p2List<Module*> list_modules;			//All Application modules inside

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	const char* GetAppName() const;
	void SetAppName(const char* name);
	const char* GetOrganizationName() const;
	void SetOrganizationName(const char* name);
	bool CleanUp();
	int framerate_cap = 30;
	bool framerate_cap_activated = false;
	float prev_last_sec_frame_count = 0;	//frames the sec before last sec.
private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();

	std::string app_name;
	std::string organization_name;

};
extern Application* App;