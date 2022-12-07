#include "ModuleEditor.h"
#include "..\Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"

#include "imgui.h"
#include "..\WindowImgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"

WindowImgui winIm;

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
	//Creating the tabs for FPS, Hardware, and Model info
	if (ImGui::Begin(FpsTab.c_str(), &tabs, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Text("The actual FrameRate is:");
	}
	ImGui::End();
	winIm.Update();

	if (ImGui::Begin(ModelTab.c_str(), &tabs, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Text("This is just a debug2");
	}
	ImGui::End();

	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			if (ImGui::MenuItem("FileInfo")){ }

			if (ImGui::MenuItem("BasicInfo2")) { }

			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit")) {
			if (ImGui::MenuItem("BasicInfo")){}

			if (ImGui::MenuItem("BasicInfo2")) {}

			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("View")) {
			if (ImGui::MenuItem("BasicInfo")) {}

			if (ImGui::MenuItem("BasicInfo2")) {}

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