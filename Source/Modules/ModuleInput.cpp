#include "..\Globals.h"
#include "..\Application.h"
#include "ModuleInput.h"
#include "../SDL/include/SDL.h"
#include "../libs/ImGui/include/imgui_impl_sdl.h"

#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleRenderExercise.h"
#include "ModuleCamera.h"
#include "ModuleEditor.h"

ModuleInput::ModuleInput()
{}

ModuleInput::~ModuleInput()
{}

bool ModuleInput::Init()
{
	SDL_Init(0);
	return true;
}

update_status ModuleInput::Update()
{
    SDL_Event event;
    char* dropfileDir;
    
    while (SDL_PollEvent(&event) != 0)
    {
        ImGui_ImplSDL2_ProcessEvent(&event);

        if (SDL_WINDOWEVENT == event.type) {
            if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
                return UPDATE_STOP;
            }
        }     
        else if (SDL_QUIT == event.type) {
            return UPDATE_STOP;
        } 

        //For dropping new models to scene
        if (SDL_DROPFILE == event.type) {
            dropfileDir = event.drop.file;
            App->rendererExercise->SetModel3D(dropfileDir);
        }
    }

    keyBoard = SDL_GetKeyboardState(NULL);
    int time = App->GetDeltaTime();

    //For camera move
    float3 newPos = float3::zero;
    float velocityCam = 0.02f;
    if (keyBoard[SDL_SCANCODE_LSHIFT]) {
        velocityCam = 0.04;
    }
    float velTime = velocityCam * time;

    if (keyBoard[SDL_SCANCODE_W]) {
        newPos.x += velTime;
    }
    if (keyBoard[SDL_SCANCODE_A]) {
        newPos.z -= velTime;
    }
    if (keyBoard[SDL_SCANCODE_S]) {
        newPos.x -= velTime;
    }
    if (keyBoard[SDL_SCANCODE_D]) {
        newPos.z += velTime;
    }
    if (keyBoard[SDL_SCANCODE_Q]) {
        newPos.y += velTime;
    }
    if (keyBoard[SDL_SCANCODE_E]) {
        newPos.y -= velTime;
    }
    App->camera->Move(newPos);

    //For camera rotation
    float3 newRot = float3::zero;
    float angleSpeed = 0.001f;
    float deltaAngle = angleSpeed * time;

    if (keyBoard[SDL_SCANCODE_SPACE]) {
        if (SDL_MOUSEMOTION == event.type) {
            if (event.button.x < (App->camera->GetWidthWindow() / 2) - (App->camera->GetWidthWindow() / 10)) { //We add this weird adding/substract to leave some space
                newRot.y += deltaAngle;                                                                        //in the middles
            }
            if (event.button.x > (App->camera->GetWidthWindow() / 2) + (App->camera->GetWidthWindow() / 10)) {
                newRot.y -= deltaAngle;
            }
            if (event.button.y < (App->camera->GetHeightWindow() / 2) - (App->camera->GetHeightWindow() / 10)) {
                newRot.x += deltaAngle;
            }
            if (event.button.y > (App->camera->GetHeightWindow() / 2) + (App->camera->GetHeightWindow() / 10) ) {
                newRot.x -= deltaAngle;
            }
        }
    }

    App->camera->Rotate(newRot);

    return UPDATE_CONTINUE;
}

bool ModuleInput::CleanUp()
{
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}
