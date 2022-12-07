#pragma once

#include "Module.h"
#include <string>

#include "../Model3D.h"

class ModuleEditor : public Module
{
public:
	ModuleEditor();
	~ModuleEditor();

	bool Init();
	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	void OutputToConsole(const char* i_textToPrint);
	void SetTargetModel(const Model3D* i_model);

private:
	std::string FpsTab = "FPS";
	std::string ModelTab = "Model Information";

};

