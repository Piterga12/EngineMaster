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
	void SetTargetModel(const Model3D* model);

private:
	std::string FpsTab = "FPS";
	std::string ModelTab = "Model Information";

};

