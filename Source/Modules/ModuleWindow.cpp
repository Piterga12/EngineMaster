#include "..\Globals.h"
#include "..\Application.h"
#include "ModuleWindow.h"
#include "ModuleEditor.h"

ModuleWindow::ModuleWindow()
{
}

ModuleWindow::~ModuleWindow()
{
}

bool ModuleWindow::Init()
{
	bool ret = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		ret = false;
	}
	else
	{
		int width = SCREEN_WIDTH;
		int height = SCREEN_HEIGHT;
		Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

		if(FULLSCREEN == true || fullScreen == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}

		window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

		if(window == NULL)
		{
			ret = false;
		}
		else
		{
			ScreenSurface = SDL_GetWindowSurface(window);
		}
	}

	return ret;
}
update_status ModuleWindow::Update() {
	if (fullScreen) { 
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN); 
	}
	else {
		SDL_SetWindowFullscreen(window, SDL_FALSE);
	}

	return UPDATE_CONTINUE;
}

bool ModuleWindow::CleanUp()
{
	if(window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	SDL_Quit();
	return true;
}

bool ModuleWindow::IsFullscreen() {
	return fullScreen;
}

void ModuleWindow::SetFullscreen(bool fs) {
	fullScreen = fs;
}
float ModuleWindow::GetBrightness() {
	return SDL_GetWindowBrightness(window);
}

void ModuleWindow::SetBrightness(float sb) {
	SDL_SetWindowBrightness(window, sb);
}

