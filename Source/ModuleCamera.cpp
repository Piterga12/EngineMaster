#include "ModuleCamera.h"

#include "Application.h"
#include "ModuleWindow.h"
#include "SDL.h"
#include "MathGeoLib_Source/Math/float3x3.h"

ModuleCamera::ModuleCamera()
{
}

ModuleCamera::~ModuleCamera()
{
}

bool ModuleCamera::Start()
{
	return true;
}

update_status ModuleCamera::Update()
{
	frustum.SetKind(FrustumProjectiveSpace::FrustumSpaceGL, FrustumHandedness::FrustumLeftHanded);

	frustum.SetFrame(float3::zero, -float3::unitZ, float3::unitY);

	frustum.SetViewPlaneDistances(0.1f, 100.0f);


	frustum.SetPerspective(2.f * atanf(tanf(math::pi / 4.0f * 0.5f) * 1), math::pi / 4.0f);

	return UPDATE_CONTINUE;
}

void ModuleCamera::SetFOVdeg(float deg)
{
	frustum.SetHorizontalFovAndAspectRatio((math::pi / 180.0f) * deg, aspectRatio);
}

void ModuleCamera::SetAspectRatio(float ratio)
{
	aspectRatio = ratio;
	frustum.SetHorizontalFovAndAspectRatio(fovRads, aspectRatio);
}
