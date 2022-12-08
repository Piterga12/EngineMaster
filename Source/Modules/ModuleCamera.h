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
	float GetHeightWindow();
	float GetWidthWindow();

	void Move(float3 newCoord);
	void Rotate(float3 i_thetasRad);

private:
	Frustum frustum;
	float fovRads;
	float aspectRatio;
};

