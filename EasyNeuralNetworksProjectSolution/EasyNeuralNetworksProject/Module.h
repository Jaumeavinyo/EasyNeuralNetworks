#ifndef __Module_H__
#define __Module_H__

class Application;

class Module
{
private:
	bool p_enabled;
	const char* p_moduleName;

public:
	Application* App;

	Module(Application* parent, bool start_enabled,const char* moduleName) : App(parent), p_enabled(start_enabled), p_moduleName(moduleName)//p_enabled init = pc
	{}



	virtual ~Module()
	{}

	virtual bool Init()
	{
		return true;
	}

	virtual bool Start()
	{
		return true;
	}

	virtual bool Draw()
	{
		return true;
	}

	virtual update_status PreUpdate(float dt)
	{
		return update_status::UPDATE_CONTINUE;
	}

	virtual update_status Update(float dt)
	{
		return update_status::UPDATE_CONTINUE;
	}

	virtual update_status PostUpdate(float dt)
	{
		return update_status::UPDATE_CONTINUE;
	}

	virtual bool CleanUp()
	{
		return true;
	}

	virtual bool isEnabled() {
		return true;
	}
};
#endif __Module_H__
