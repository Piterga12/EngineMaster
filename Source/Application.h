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

class Application
{
public:

	Application();
	~Application();

	bool Init();
	bool Start();
	update_status Update();
	bool CleanUp();

public:
	ModuleRender* renderer = nullptr;
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleProgram* program = nullptr;
	ModuleRenderExercise* rendererExercise = nullptr;
	ModuleDebugDraw* debugDraw = nullptr;
	ModuleEditor* editor = nullptr;
	ModuleCamera* camera = nullptr;

private:

	std::list<Module*> modules;

};

extern Application* App;