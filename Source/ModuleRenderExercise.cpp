#include "ModuleRenderExercise.h"
#include "Application.h"
#include "ModuleProgram.h"
#include "MathGeoLib_Source/Geometry/Frustum.h"
#include "ModuleDebugDraw.h"
#include "debugdraw.h"

#define VERT_SHADER "VertexShader.glsl"
#define FRAG_SHADER "FragmentShader.glsl"


ModuleRenderExercise::ModuleRenderExercise()
{
}

ModuleRenderExercise::~ModuleRenderExercise()
{
	glDeleteBuffers(1, &vbo);
}

bool ModuleRenderExercise::Init()
{
	float vtx_data[] = { -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f };

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // set vbo active
	glBufferData(GL_ARRAY_BUFFER, sizeof(vtx_data), vtx_data, GL_STATIC_DRAW);

	return true;
}


bool ModuleRenderExercise::Start()
{
	program = App->program->CreateProgramFromShaders(VERT_SHADER, FRAG_SHADER);

	return true;
}

update_status ModuleRenderExercise::Update()
{
	// We declare frustum
	Frustum frustum;

	//frustum.type = FrustumType::PerspectiveFrustum;
	frustum.SetKind(FrustumProjectiveSpace::FrustumSpaceGL, FrustumHandedness::FrustumLeftHanded);
	
	frustum.SetFrame(float3::zero, -float3::unitZ, float3::unitY);

	frustum.SetViewPlaneDistances(0.1f, 100.0f);


	frustum.SetPerspective(2.f * atanf(tanf(math::pi / 4.0f * 0.5f) * 1), math::pi / 4.0f);

	float4x4 proj = frustum.ProjectionMatrix();
	float4x4 view = frustum.ViewProjMatrix();
	float4x4 model = float4x4::FromTRS(float3(2.0f, 0.0f, 0.0f),
		float4x4::RotateZ(pi / 4.0f),
		float3(2.0f, 1.0f, 0.0f));

	//Axis and Grid drawing
	dd::axisTriad(float4x4::identity, 0.2f, 1.0f);
	dd::xzSquareGrid(-10, 10, 0.0f, 1.0f, dd::colors::Gray);
	App->debugDraw->Draw(view, proj, SCREEN_WIDTH, SCREEN_HEIGHT);

	// This part is for drawing the triangle 
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	
	// This part if or using transform in shaders

	glUseProgram(program);
	glUniformMatrix4fv(0, 1, GL_TRUE, &model[0][0]);
	glUniformMatrix4fv(1, 1, GL_TRUE, &view[0][0]);
	glUniformMatrix4fv(2, 1, GL_TRUE, &proj[0][0]);

		
	glDrawArrays(GL_TRIANGLES, 0, 3);


	return UPDATE_CONTINUE;
}
