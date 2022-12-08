#pragma once

#include "Globals.h"
#include <string>
#include <vector>

class WindowImgui
{
public:

	WindowImgui();
	~WindowImgui();

	void Start();
	update_status Update();

protected:
	std::string FpsTab = "FPS";
	std::string HwTab = "HardWare";
	std::string WinTab = "Window";

	std::vector<float> FpsHist;
	int FpsCaptures = 100;
	int CurrentIndex = 0;

	std::string SdlVersion;
	std::string CpusAndCache;
	float Ram;
	std::string GpuVendor;
	std::string GpuBrand;
};

