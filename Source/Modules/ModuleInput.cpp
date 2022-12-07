#include "..\Globals.h"
#include "..\Application.h"
#include "ModuleInput.h"

#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleCamera.h"
#include "ModuleEditor.h"
#include "ModuleRenderExercise.h"

#include "../SDL/include/SDL.h"
#include "../libs/ImGui/include/imgui_impl_sdl.h"

ModuleInput::ModuleInput()
{}

ModuleInput::~ModuleInput()
{}

bool ModuleInput::Init()
{
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		ret = false;
	}

	return ret;
}

update_status ModuleInput::Update()
{
    SDL_Event sdlEvent;

    char* dropfileDir;

    while (SDL_PollEvent(&sdlEvent) != 0)
    {
        ImGui_ImplSDL2_ProcessEvent(&sdlEvent);
        switch (sdlEvent.type)
        {
            case SDL_QUIT:
                return UPDATE_STOP;
            case SDL_WINDOWEVENT:
                if (sdlEvent.window.event == SDL_WINDOWEVENT_RESIZED || sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) 
                    App->renderer->WindowResized(sdlEvent.window.data1, sdlEvent.window.data2);
                if (sdlEvent.window.event == SDL_WINDOWEVENT_CLOSE)
                    return UPDATE_STOP;
                break;
            case SDL_DROPFILE:
                dropfileDir = sdlEvent.drop.file;
                App->rendererExercise->SetModel3D(dropfileDir);
                break;
        }
    }

    keyBoard = SDL_GetKeyboardState(NULL);
    int deltaTime = App->GetDeltaTime();

    //For camera move
    float3 deltaPosVec = float3::zero;
    float cameraSpeed = 0.02f;
    if (keyBoard[SDL_SCANCODE_LSHIFT])
        cameraSpeed *= 2;
    float deltaPos = cameraSpeed * deltaTime;

    if (keyBoard[SDL_SCANCODE_W]) {
        deltaPosVec.x += deltaPos;
    }
    if (keyBoard[SDL_SCANCODE_S]) {
        deltaPosVec.x -= deltaPos;
    }
    if (keyBoard[SDL_SCANCODE_Q]) {
        deltaPosVec.y += deltaPos;
    }
    if (keyBoard[SDL_SCANCODE_E]) {
        deltaPosVec.y -= deltaPos;
    }
    if (keyBoard[SDL_SCANCODE_D]) {
        deltaPosVec.z += deltaPos;
    }
    if (keyBoard[SDL_SCANCODE_A]) {
        deltaPosVec.z -= deltaPos;
    }
    App->camera->Translate(deltaPosVec);

    //For camera rotation
    float3 deltaRot = float3::zero;
    float angleSpeed = 0.005f;
    float deltaAngle = angleSpeed * deltaTime;

    if (keyBoard[SDL_SCANCODE_LEFT]) {
        deltaRot.y += deltaAngle;
    }
    if (keyBoard[SDL_SCANCODE_RIGHT]) {
        deltaRot.y -= deltaAngle;
    }
    if (keyBoard[SDL_SCANCODE_UP]) {
        deltaRot.x += deltaAngle;
    }
    if (keyBoard[SDL_SCANCODE_DOWN]) {
        deltaRot.x -= deltaAngle;
    }
    App->camera->Rotate(deltaRot);

    return UPDATE_CONTINUE;
}

bool ModuleInput::CleanUp()
{
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}
