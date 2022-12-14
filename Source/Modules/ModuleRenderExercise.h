#pragma once

#include "Module.h"

#include <GL/glew.h>

#include "..\libs\MathGeoLib\Include\Math\float4x4.h"

#include "..\Model.h"

class ModuleRenderExercise : public Module
{
public:
	ModuleRenderExercise();
	~ModuleRenderExercise();

	bool Init();
	bool Start();
	update_status Update();

	float4x4 GetModel() {
		return m_model;
	}

	GLuint GetProgram() {
		return m_program;
	}

	void SetModel3D(const char* i_modelPath);

private:
	GLuint m_vbo;
	GLuint m_program;
	Model* m_model3D;
	float4x4 m_model;
};

