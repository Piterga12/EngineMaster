#pragma once
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleProgram.h"
#include "ModuleCamera.h"
#include "ModuleRenderExercise.h"
#include "ModuleEditor.h"
#include "ModuleDebugDraw.h"
#include "ModuleTexture.h"
#include "Timer.h"

#include "WindowImgui.h"

using namespace std;

Timer myTimer;
WindowImgui WinFps;

Application::Application()
{
	modules.push_back(editor = new ModuleEditor());
	modules.push_back(window = new ModuleWindow());
	modules.push_back(renderer = new ModuleRender());
	modules.push_back(input = new ModuleInput());
	modules.push_back(program = new ModuleProgram());
	modules.push_back(camera = new ModuleCamera());
	modules.push_back(rendererExercise = new ModuleRenderExercise());
	modules.push_back(debugDraw = new ModuleDebugDraw());
	modules.push_back(texture = new ModuleTexture());
	
}

Application::~Application()
{
	for(list<Module*>::iterator it = modules.begin(); it != modules.end(); ++it)
    {
        delete *it;
    }
}

bool Application::Init()
{
	bool ret = true;

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
		ret = (*it)->Init();

	return ret;
}

bool Application::Start()
{
	bool ret = true;

	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
		ret = (*it)->Start();

	myTimer.Start();
	PrevTime = myTimer.Read();

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	int actualTime = myTimer.Read();
	DeltaTime = actualTime - PrevTime;

	float timePerFrame = 0.f;

	if (0 < GetFps())
		timePerFrame = 1000.f / GetFps();
	//PERSLOG("%f", WinFps.GetFps());
	if (timePerFrame < DeltaTime) {
		for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
			ret = (*it)->PreUpdate();

		for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
			ret = (*it)->Update();

		for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
			ret = (*it)->PostUpdate();
		PrevTime = actualTime;
	}
	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(list<Module*>::reverse_iterator it = modules.rbegin(); it != modules.rend() && ret; ++it)
		ret = (*it)->CleanUp();

	return ret;
}

int Application::GetDeltaTime() {
	return DeltaTime;
}
float Application::GetFps() {
	return MaxFps;
}
void Application::SetFps(float numFps) {
	MaxFps = numFps;

}
