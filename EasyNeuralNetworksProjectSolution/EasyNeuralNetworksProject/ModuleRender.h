#ifndef MODULE_RENDER_H
#define MODULE_RENDER_H

#include "Globals.h"
#include "Module.h"


class ModuleRender : public Module {

public:

	SDL_Renderer*   renderer;
	SDL_Rect		camera;
	SDL_Rect		viewport;
	SDL_Color		background;

public:
	
	ModuleRender(Application* app, const char* moduleName, bool start_enabled);

	// Destructor
	virtual ~ModuleRender();

	// Called before render is available
	bool Init(/*pugi::xml_node&*/);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);

	// Called before quitting
	bool CleanUp();

	// Save and Load
	

	// Utils
	void SetViewPort(const SDL_Rect& rect);
	void ResetViewPort();
	void ScreenToWorld(int* x, int* y) const;
	iPoint ScreenToWorld(int x, int y) const;
	void setBackgroundColor(int R, int G, int B, int A = 1);

	// Draw & Blit
	/*bool Blit(SDL_Texture* texture, int x, int y, const SDL_Rect* section = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE, bool use_camera = true, float scale_ = 1.0f, SDL_Renderer* renderer_ = App->render->renderer, float speed = 1.0f, double angle = 0, int pivot_x = INT_MAX, int pivot_y = INT_MAX) const;
	bool DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool filled = true, bool use_camera = true) const;
	bool DrawLine(int x1, int y1, int x2, int y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool use_camera = true) const;
	bool DrawCircle(int x1, int y1, int redius, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool use_camera = true) const;

	bool InsideCamera(const SDL_Rect& rect)const;*/

	
	// Set background color
	void SetBackgroundColor(SDL_Color color);
	


};

class ImageRender{

public:

	ImageRender(uint order, SDL_Texture* texture, int x, int y, const SDL_Rect* section, float scale, float speed, double angle, int pivot_x, int pivot_y, SDL_Rect rect) :
		order(order), tex(texture), x(x), y(y), section(section), scale(scale), speed(speed), angle(angle), pivot_x(pivot_x), pivot_y(pivot_y), rect(rect) {}

	uint Ordering()const
	{
		return order;
	}

public:
	SDL_Texture* tex;
	int					x;
	int					y;
	const SDL_Rect* section;
	SDL_Rect			rect;
	float				scale;
	float				speed;
	double				angle;
	int					pivot_x;
	int					pivot_y;

	uint				order;
};

#endif MODULE_RENDER_H
