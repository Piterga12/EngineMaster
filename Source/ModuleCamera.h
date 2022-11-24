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

	void SetFOVdeg(float deg);
	void SetAspectRatio(float ratio);
	float4x4 proj{ frustum.ProjectionMatrix() };
	float4x4 view{ frustum.ViewProjMatrix() };
	float4x4 model{ float4x4::FromTRS(float3(2.0f, 0.0f, 0.0f),
		float4x4::RotateZ(pi / 4.0f),
		float3(2.0f, 1.0f, 0.0f)) };
private:
	// We declare frustum
	Frustum frustum;

	float fovRads;
	float aspectRatio;
};
