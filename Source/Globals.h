#pragma once
#include <windows.h>
#include <stdio.h>

#define PERSLOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

void log(const char file[], int line, const char* format, ...);

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

enum CamMoves
{
	MOVE_STRAIGHT = 1,
	MOVE_RIGTH,
	MOVE_LEFT,
	MOVE_BACK,
	MOVE_UP,
	MOVE_DOWN,
	ROTATE_UP,
	ROTATE_DOWN,
	ROTATE_RIGHT,
	ROTATE_LEFT,
	ROTATE_FREE
};

//Const
#define DEGTORAD 0.01745329251f

// Configuration -----------
#define GLSL_VERSION "version 460"
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define FULLSCREEN false
#define VSYNC true
#define TITLE "Super Awesome Engine"