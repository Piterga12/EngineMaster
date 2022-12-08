#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__

#include "Module.h"
#include "..\SDL/include/SDL.h"

class Application;

class ModuleWindow : public Module
{
public:

	ModuleWindow();

	virtual ~ModuleWindow();
	bool Init();
	bool CleanUp();
	update_status Update();
	SDL_Window* window = NULL;
	SDL_Surface* ScreenSurface = NULL;

	bool IsFullscreen();
	void SetFullscreen(bool fs);
	float GetBrightness();
	void SetBrightness(float sb);

private:
	bool fullScreen = false;
	
};

#endif