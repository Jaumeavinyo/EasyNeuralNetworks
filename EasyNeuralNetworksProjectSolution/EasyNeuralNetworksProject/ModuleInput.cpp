#include "ModuleInput.h"
#include "App.h"


//############  CONSTRUCTORS ############


ModuleInput::ModuleInput(Application* app, const char* moduleName, bool start_enabled) : Module(app, start_enabled, moduleName) {

	p_keyboard = new KeyState[MAX_KEYS];
	memset(p_keyboard, KEY_IDLE, sizeof(KeyState) * MAX_KEYS);
	memset(p_mouse_buttons, KEY_IDLE, sizeof(KeyState) * NUM_MOUSE_BUTTONS);
}

// Destructor
ModuleInput::~ModuleInput(){
	delete[] p_keyboard;
}


//############  MAIN APP FUNCTIONS ############


// Called before render is available
bool ModuleInput::Init(){
	printf("ModuleInput Init()\n");
	bool ret = true;
	SDL_Init(0);

	if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		printf("---> SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called before the first frame
bool ModuleInput::Start()
{
	SDL_StopTextInput();
	return true;
}

// Called each loop iteration
update_status ModuleInput::PreUpdate(float dt)
{
	static SDL_Event event;

	const Uint8* keys = SDL_GetKeyboardState(NULL);

	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keys[i] == 1)
		{
			if (p_keyboard[i] == KEY_IDLE)
				p_keyboard[i] = KEY_DOWN;
			else
				p_keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if (p_keyboard[i] == KEY_REPEAT || p_keyboard[i] == KEY_DOWN)
				p_keyboard[i] = KEY_UP;
			else
				p_keyboard[i] = KEY_IDLE;
		}
	}
	for (int i = 0; i < NUM_MOUSE_BUTTONS; ++i)
	{
		if (p_mouse_buttons[i] == KEY_DOWN)
			p_mouse_buttons[i] = KEY_REPEAT;

		if (p_mouse_buttons[i] == KEY_UP)
			p_mouse_buttons[i] = KEY_IDLE;
	}

	while (SDL_PollEvent(&event) != 0)
	{
		switch (event.type)
		{
		case SDL_QUIT:
			p_windowEvents[WE_QUIT] = true;
			break;

		case SDL_WINDOWEVENT:
			switch (event.window.event)
			{
				//case SDL_WINDOWEVENT_LEAVE:
			case SDL_WINDOWEVENT_HIDDEN:
			case SDL_WINDOWEVENT_MINIMIZED:
			case SDL_WINDOWEVENT_FOCUS_LOST:
				p_windowEvents[WE_HIDE] = true;
				break;

				//case SDL_WINDOWEVENT_ENTER:
			case SDL_WINDOWEVENT_SHOWN:
			case SDL_WINDOWEVENT_FOCUS_GAINED:
			case SDL_WINDOWEVENT_MAXIMIZED:
			case SDL_WINDOWEVENT_RESTORED:
				p_windowEvents[WE_SHOW] = true;
				break;
			}
			break;

		case SDL_MOUSEBUTTONDOWN:
			p_mouse_buttons[event.button.button - 1] = KEY_DOWN;
			
			break;

		case SDL_MOUSEBUTTONUP:
			p_mouse_buttons[event.button.button - 1] = KEY_UP;
			
			break;

		case SDL_MOUSEMOTION:
			int scale = App->window->scale;
			p_mouse_motion_x = event.motion.xrel / scale;
			p_mouse_motion_y = event.motion.yrel / scale;
			p_mouse_x = event.motion.x / scale;
			p_mouse_y = event.motion.y / scale;
			
			break;
		}
	}

	return update_status::UPDATE_CONTINUE;
}


bool ModuleInput::CleanUp()
{
	
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}


//############  UTILITY FUNCTIONS ############


bool ModuleInput::GetWindowEvent(EventWindow ev)
{
	return p_windowEvents[ev];
}

void ModuleInput::GetMousePosition(int& x, int& y)
{
	x = p_mouse_x;
	y = p_mouse_y;
}

void ModuleInput::GetMouseMotion(int& x, int& y)
{
	x = p_mouse_motion_x;
	y = p_mouse_motion_y;
}