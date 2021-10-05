#ifndef GLOBALS_H_
#define GLOBALS_H_

//#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

#include "StandartLibraries.h"
#include "lib/SDL2/include/SDL.h"
#include <SDL.h>
#include "Variables.h"
//void log(const char file[], int line, const char* format, ...);


#include "p2List.h"


enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR

};



// Window Configuration -----------
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define SCREEN_SIZE 1  //must be an integer
#define WIN_FULLSCREEN false
#define WIN_RESIZABLE true
#define WIN_BORDERLESS false
#define WIN_FULLSCREEN_DESKTOP false
#define VSYNC true //imgui main.cpp uses it
#define WIN_DOUBLE_BUFFERING false // glew.h stuff  //imgui main.cpp uses it
#define SDL_WIN_OPENGL true //imgui main.cpp uses it
#define SDL_WIN_ALLOW_HIGHDPI true
#define TITLE "Easy Neural Networks"


#endif GLOBALS_H_