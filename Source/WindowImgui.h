#pragma once

#include "Globals.h"
#include <string>
#include <vector>

class WindowImgui
{
public:

	WindowImgui();
	~WindowImgui();

	float GetFps() {
		return MaxFps;
	}

	void SetFps(float numFps) {
		MaxFps = numFps;
	}

	void Start();
	update_status Update();

protected:
	float MaxFps = 60.0f;

	std::string FpsTab = "FPS";
	std::string HwTab = "HardWare";

	std::vector<float> FpsHist;
	int FpsCaptures = 100;
	int CurrentIndex = 0;

	std::string SdlVersion;
	std::string CpusAndCache;
	std::string Ram;
	std::string GpuVendor;
	std::string GpuBrand;
};

