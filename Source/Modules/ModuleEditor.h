#pragma once

#include "Module.h"
#include <string>

class ModuleEditor : public Module
{
public:
	bool Init();
	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

private:
	std::string FpsTab = "FPS";
	std::string ModelTab = "Model Information";
};
