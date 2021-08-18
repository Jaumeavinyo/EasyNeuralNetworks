#ifndef MODULE_INPUT_H
#define MODULE_INPUT_H



#include "Globals.h"
#include "Module.h"

//#define NUM_KEYS 352
#define NUM_MOUSE_BUTTONS 5
//#define LAST_KEYS_PRESSED_BUFFER 50

#define MAX_KEYS 300

struct SDL_Rect;

enum EventWindow
{
	WE_QUIT = 0,
	WE_HIDE = 1,
	WE_SHOW = 2,
	WE_COUNT
};

enum KeyState
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

class ModuleInput : public Module
{

public:

	ModuleInput(Application* app, const char* moduleName, bool start_enabled);

	// Destructor
	virtual ~ModuleInput();

	// Called before render is available
	bool Init() override;

	// Called before the first frame
	bool Start() override;

	// Called each loop iteration
	update_status PreUpdate(float dt);

	// Called before quitting
	bool CleanUp() override;

	// Gather relevant win events
	bool GetWindowEvent(EventWindow ev);

	// Check key states (includes mouse and joy buttons)
	KeyState GetKey(int id) const
	{
		return p_keyboard[id];
	}

	KeyState GetMouseButtonDown(int id) const
	{
		return p_mouse_buttons[id - 1];
	}

	KeyState GetKey(int id);
	// Check if a certain window event happened
	bool GetWindowEvent(int code);

	// Get mouse / axis position
	void GetMousePosition(int& x, int& y);
	void GetMouseMotion(int& x, int& y);

private:
	bool		p_windowEvents[WE_COUNT];
	KeyState*   p_keyboard;
	KeyState	p_mouse_buttons[NUM_MOUSE_BUTTONS];
	int			p_mouse_motion_x;
	int			p_mouse_motion_y;
	int			p_mouse_x;
	int			p_mouse_y;
};


#endif MODULE_INPUT_H