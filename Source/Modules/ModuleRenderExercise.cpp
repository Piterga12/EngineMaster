#include "ModuleRenderExercise.h"
#include "..\Application.h"
#include "ModuleProgram.h"
#include "ModuleDebugDraw.h"
#include "..\debugdraw.h"
#include "ModuleCamera.h"

#define VERT_SHADER "VertexShader.glsl"
#define FRAG_SHADER "FragmentShader.glsl"

using namespace dd;

ModuleRenderExercise::ModuleRenderExercise()
{
	model = float4x4::identity;

	float4x4::FromTRS(float3(2.0f, 0.0f, 0.0f),
		float4x4::RotateZ(pi / 4.0f),
		//float3(0.01f, 0.01f, 0.01f)
		float3(1.0f, 1.0f, 1.0f)
	);
}

ModuleRenderExercise::~ModuleRenderExercise()
{
	glDeleteBuffers(1, &vbo);
	glDeleteProgram(program);
}

bool ModuleRenderExercise::Init()
{
	float vtx_data[] = {
		-1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f
	};

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
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
	

	// This part is for drawing the triangle 
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(float) * 3 * 6) /*buffer offset*/);
	
	
	
	// This part if or using transform in shaders
	glUseProgram(program);
	glUniformMatrix4fv(0, 1, GL_TRUE, &model[0][0]);
	//glUniformMatrix4fv(1, 1, GL_TRUE, & App->camera->GetViewMatrix()[0][0]);
	//glUniformMatrix4fv(2, 1, GL_TRUE, & App->camera->GetProjectionMatrix()[0][0]);

		
	glDrawArrays(GL_TRIANGLES, 0, 3*2);


	return UPDATE_CONTINUE;
}
