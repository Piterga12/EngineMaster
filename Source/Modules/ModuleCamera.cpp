#include "ModuleCamera.h"

#include "..\Application.h"
#include "ModuleWindow.h"
#include "SDL.h"
#include "../MathGeoLib_Source/Math/float3x3.h"

ModuleCamera::ModuleCamera()
{
}

ModuleCamera::~ModuleCamera()
{
}

bool ModuleCamera::Start()
{
	aspectRatio = ((float)SCREEN_WIDTH) / ((float)SCREEN_HEIGHT);
	return true;
}

update_status ModuleCamera::Update()
{
	frustum.SetKind(FrustumProjectiveSpace::FrustumSpaceGL, FrustumHandedness::FrustumLeftHanded);
	frustum.SetFrame(float3::zero, -float3::unitZ, float3::unitY);
	frustum.SetViewPlaneDistances(0.1f, 100.0f);
	frustum.SetPerspective(2.f * atanf(tanf(math::pi / 4.0f * 0.5f) * 1), math::pi / 4.0f);
	frustum.SetHorizontalFovAndAspectRatio((math::pi / 180.0f) * 90.0f, aspectRatio);


	view = frustum.ViewProjMatrix();
	proj = frustum.ProjectionMatrix();
	model = float4x4::FromTRS(float3(2.0f, 0.0f, 0.0f),
		float4x4::RotateZ(pi / 4.0f),
		float3(2.0f, 1.0f, 0.0f));

	int weidth, height;
	SDL_GetWindowSize(App->window->window, &weidth, &height);
	aspectRatio = ((float)weidth) / ((float)height);
	frustum.SetHorizontalFovAndAspectRatio((math::pi / 180.0f) * 90.0f, aspectRatio);

	return UPDATE_CONTINUE;
}
