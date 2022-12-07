#pragma once

#include "Module.h"
#include <GL\glew.h>
#include "../../Source/MathGeoLib_Source/Math/float4x4.h"

class ModuleRenderExercise : public Module
{
public:
	ModuleRenderExercise();
	~ModuleRenderExercise();

	bool Init();
	bool Start();
	update_status Update();

private:
	float4x4 model;

	GLuint vbo;
	GLuint program;

};
