#ifndef GLOBALS_H_
#define GLOBALS_H_

//#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

#include "StandartLibraries.h"

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
#define SCREEN_SIZE 0.7
#define WIN_FULLSCREEN false
#define WIN_RESIZABLE true
#define WIN_BORDERLESS false
#define WIN_FULLSCREEN_DESKTOP false
#define VSYNC false
#define WIN_DOUBLE_BUFFERING false // glew.h stuff
#define TITLE "Easy Neural Networks"


#endif GLOBALS_H_