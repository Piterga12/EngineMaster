#pragma once

#include<list>
#include "Globals.h"
#include ".\Modules\Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleProgram;
class ModuleRenderExercise;
class ModuleEditor;
class ModuleDebugDraw;
class ModuleCamera;
class Timer;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	bool Start();
	update_status Update();
	bool CleanUp();

	ModuleRender* renderer = nullptr;
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleProgram* program = nullptr;
	ModuleRenderExercise* rendererExercise = nullptr;
	ModuleDebugDraw* debugDraw = nullptr;
	ModuleEditor* editor = nullptr;
	ModuleCamera* camera = nullptr;

	int GetDeltaTime() {
		return DeltaTime;
	}

private:

	std::list<Module*> modules;

	int PrevTime = 0;
	int DeltaTime = 0;

};

extern Application* App;