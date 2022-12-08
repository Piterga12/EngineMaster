#include "WindowImgui.h"

#include <cmath>

#include "./libs/ImGui/Include/imgui.h"
#include "GL/glew.h"
#include "SDL.h"

#include "Application.h"
#include "ModuleWindow.h"

WindowImgui::WindowImgui()
{
	SdlVersion = std::to_string(SDL_MAJOR_VERSION) + "." + std::to_string(SDL_MINOR_VERSION) + "." + std::to_string(SDL_PATCHLEVEL);

	int cacheSizeInB = SDL_GetCPUCacheLineSize();
	int cacheSizeInKB = std::ceil(cacheSizeInB / 1000.f);
	int cacheSizeInKb = cacheSizeInKB * 8;
	CpusAndCache = std::to_string(SDL_GetCPUCount()) + " (Cache: " + std::to_string(cacheSizeInKb) + "kb)";

	int ramInMB = SDL_GetSystemRAM();
	float ramInGB = ramInMB / 1000.f;
	float ramInGb = ramInGB * 8.f;

	int ramInGbOneDecimalAux = std::ceil(ramInGb * 10.f);

	Ram = (float)SDL_GetSystemRAM() / 1024.f;

	FpsHist = std::vector<float>(FpsCaptures);
	
}

WindowImgui::~WindowImgui()
{
}

void WindowImgui::Start()
{
	char glVendor[128];
	sprintf(glVendor, "%s", glGetString(GL_VENDOR));
	GpuVendor = _strdup(glVendor);
	char glRenderer[128];
	sprintf(glRenderer, "%s", glGetString(GL_RENDERER));
	GpuBrand = _strdup(glRenderer);
}

update_status WindowImgui::Update()
{
	bool enabled;
	bool fullscreen = App->window->IsFullscreen();
	float brightness = App->window->GetBrightness();

	if (ImGui::Begin(FpsTab.c_str(), &enabled, ImGuiWindowFlags_AlwaysAutoResize)) {
		float mFps = App->GetFps();
		//PERSLOG("%f", mFps);
		ImGui::SliderFloat("Max FPS", &mFps, 0.f, 150.f, "%.11f", ImGuiSliderFlags_AlwaysClamp);
		App->SetFps(mFps);
		ImGui::Text("Maximun of FPS: %f", mFps);

		int deltaTime = App->GetDeltaTime();
		FpsHist[CurrentIndex] = 1000.f / deltaTime;

		char currentFramerate[25];
		sprintf_s(currentFramerate, 25, "Framerate %.1f", FpsHist[CurrentIndex]);
		ImGui::PlotHistogram("##framerate", &FpsHist[0], FpsCaptures, 0, currentFramerate, 0.f, 160.f, ImVec2(310, 160));

		if (CurrentIndex < FpsCaptures - 1) {
			++CurrentIndex;
		}
		else {
			FpsHist.erase(FpsHist.begin());
			FpsHist.push_back(0);
		}
	}
	ImGui::End();

	if (ImGui::Begin(WinTab.c_str(), &enabled, ImGuiWindowFlags_AlwaysAutoResize)) {
		
		ImGui::Text("Change to:");
		if (ImGui::Checkbox("Fullscreen", &fullscreen)) {
			App->window->SetFullscreen(fullscreen);
		}
		if (ImGui::SliderFloat("Brightness", &brightness, 0.0f, 1.0f)) {
			App->window->SetBrightness(brightness);
		}
		

	}
	ImGui::End();

	if (ImGui::Begin(HwTab.c_str(), &enabled, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::TextUnformatted(("SDL Version: " + SdlVersion).c_str());

		ImGui::Separator();

		ImGui::TextUnformatted(("CPUs: " + CpusAndCache).c_str());
		ImGui::Text("System RAM: %.1f %s", Ram, "GB");

		ImGui::Separator();

		ImGui::TextUnformatted(("GPU: " + GpuVendor).c_str());
		ImGui::TextUnformatted(("Brand: " + GpuBrand).c_str());
	}
	ImGui::End();

	return UPDATE_CONTINUE;
}