#pragma once

#include "Module.h"
#include "MathGeoLib_Source/Geometry/Frustum.h"

class ModuleCamera : public Module
{
public:
	ModuleCamera();
	~ModuleCamera();

	bool Start();
	update_status Update();

	float4x4 proj;
	float4x4 view;
	float4x4 model;
private:
	// We declare frustum
	Frustum frustum;

	float fovRads;
	float aspectRatio;
};
