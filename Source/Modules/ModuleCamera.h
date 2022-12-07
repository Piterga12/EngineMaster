#pragma once

#include "Module.h"
#include "..\libs\MathGeoLib\Include\Geometry\Frustum.h"

class ModuleCamera : public Module
{
public:
	ModuleCamera();
	~ModuleCamera();

	bool Start();
	update_status Update();

	float4x4 GetProjection();
	float4x4 GetView();

	void Translate(float3 i_deltaCoords);
	void Rotate(float3 i_thetasRad);

private:
	Frustum frustum;

	float fovRads;
	float aspectRatio;
};

