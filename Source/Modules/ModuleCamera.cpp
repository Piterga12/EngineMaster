#include "ModuleCamera.h"

#include "..\Application.h"
#include "ModuleWindow.h"
#include "SDL.h"
#include "../MathGeoLib/Include/Math/float3x3.h"

ModuleCamera::ModuleCamera()
{
}

ModuleCamera::~ModuleCamera()
{
}

bool ModuleCamera::Start()
{
	frustum.SetKind(FrustumProjectiveSpace::FrustumSpaceGL, FrustumHandedness::FrustumRightHanded);
	frustum.SetPos(float3(0.0f, 3.0f, 5.0f));
	frustum.SetFront(-float3::unitZ);
	frustum.SetUp(float3::unitY);

	frustum.SetViewPlaneDistances(0.1f, 100.0f);

	int weidth, height;
	SDL_GetWindowSize(App->window->window, &weidth, &height);
	aspectRatio = ((float)weidth) / ((float)height);
	fovRads = ((math::pi / 180.f) * 90.f);
	frustum.SetHorizontalFovAndAspectRatio(fovRads, aspectRatio);

	return true;
}

update_status ModuleCamera::Update()
{
	int weidth, height;
	SDL_GetWindowSize(App->window->window, &weidth, &height);
	aspectRatio = ((float)weidth) / ((float)height);
	frustum.SetHorizontalFovAndAspectRatio(fovRads, aspectRatio);

	return UPDATE_CONTINUE;
}

float4x4 ModuleCamera::GetProjection() {
	return frustum.ProjectionMatrix();
}
float4x4 ModuleCamera::GetView() {
	return frustum.ViewMatrix();
}

void ModuleCamera::Translate(float3 i_deltaCoords)
{
	float3 deltaCoordsWithRespectFront = frustum.Front().Mul(i_deltaCoords);

	float3 translationColumn = float3::zero;
	translationColumn += frustum.Front().Normalized() * i_deltaCoords.x;
	translationColumn += float3::unitY * i_deltaCoords.y;
	translationColumn += frustum.WorldRight().Normalized() * i_deltaCoords.z;

	float4x4 translationMat = float4x4(float3x4(float3x3::identity, translationColumn));

	float3 oldPos = frustum.Pos();
	float3 translatedPos = (translationMat * float4(oldPos, 1.0f)).xyz();

	frustum.SetPos(translatedPos);
}

void ModuleCamera::Rotate(float3 i_thetasRad)
{
	float3x3 rotX = float3x3::RotateAxisAngle(frustum.WorldRight(), i_thetasRad.x);
	float3x3 rotY = float3x3::RotateY(i_thetasRad.y);
	float3x3 rotZ = float3x3::RotateAxisAngle(frustum.Front(), i_thetasRad.z);
	float3x3 totalRot = rotY * rotX * rotZ;

	float3 oldLook = frustum.Front().Normalized();
	float3 newLook = totalRot.MulDir(oldLook);

	float3 oldUp = frustum.Up().Normalized();
	float3 newUp = totalRot.MulDir(oldUp);

	if (newUp.y < 0.f) { 
		totalRot = rotY * float3x3::identity * rotZ;

		newLook = totalRot.MulDir(oldLook);
		newUp = totalRot.MulDir(oldUp);
	}

	frustum.SetFront(newLook);
	frustum.SetUp(newUp);
}

