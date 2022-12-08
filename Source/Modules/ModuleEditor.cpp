#include "ModuleEditor.h"
#include "..\Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"

#include "..\WindowImgui.h"
#include "../libs/ImGui/include/imgui_impl_opengl3.h"
#include "../libs/ImGui/include/imgui_impl_sdl.h"
#include <string>

WindowImgui winIm;

ModuleEditor::ModuleEditor()
{
}

ModuleEditor::~ModuleEditor()
{
}

bool ModuleEditor::Init()
{
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	return true;
}

bool ModuleEditor::Start()
{
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer->context);
	ImGui_ImplOpenGL3_Init("#version 130");
	controls = false;
	winIm.Start();

	return true;
}

update_status ModuleEditor::PreUpdate()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	ImGui::NewFrame();

	return UPDATE_CONTINUE;
}

update_status ModuleEditor::Update()
{
	bool tabs;
	//Creating the tabs
	winIm.Update();

	if (controls == true) {
		if (ImGui::Begin(ControlsTab.c_str(), &tabs, ImGuiWindowFlags_AlwaysAutoResize)) {
			ImGui::Text("Move the camera with W,A,S,D,Q,E\n");
			ImGui::Text("Rotate the camera while pressing SPACE moving the mouse\n");
			ImGui::Text("Change the 3D Model by dropping the new one from models folder\n");
		}
		ImGui::End();
	}
	

	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			if (ImGui::MenuItem("FileInfo")) {} //Doesn't do anything

			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help")) {
			if (ImGui::MenuItem("Controls")) {
				controls = true;
			}

			if (ImGui::MenuItem("Github Repository")) {
				ShellExecuteA(NULL, "open", "https://github.com/Piterga12/EngineMaster", NULL, NULL, SW_SHOWNORMAL);
			}

			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Exit")) {
			return UPDATE_STOP;

			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}


	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
		SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
	}

	return UPDATE_CONTINUE;
}

update_status ModuleEditor::PostUpdate()
{
	return UPDATE_CONTINUE;
}

bool ModuleEditor::CleanUp()
{
	ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

	return true;
}

void ModuleEditor::SetTargetModel(const Model* i_model)
{
}
