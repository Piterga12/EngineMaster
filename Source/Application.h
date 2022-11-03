#pragma once

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleRenderExercise;
class ModuleEditor;
class ModuleRender;
class ModuleDebugDraw;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	ModuleRender* renderer = nullptr;
	ModuleRenderExercise* rendererExercise = nullptr;
	ModuleEditor* editor = nullptr;
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleDebugDraw* debugDraw = nullptr;

private:

	std::list<Module*> modules;

};

extern Application* App;
