#pragma once

#include "Module.h"
#include <string>

#include "../Model.h"

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
	void SetTargetModel(const Model* model);

private:
	bool controls;
	std::string ControlsTab = "Controls";
};

