#include "ModuleRenderExercise.h"
#include "Application.h"
#include "ModuleProgram.h"
#include "ModuleDebugDraw.h"
#include "debugdraw.h"
#include "ModuleCamera.h"

#define VERT_SHADER "VertexShader.glsl"
#define FRAG_SHADER "FragmentShader.glsl"

using namespace dd;

ModuleRenderExercise::ModuleRenderExercise()
{
}

ModuleRenderExercise::~ModuleRenderExercise()
{
	glDeleteBuffers(1, &vbo);
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
	//Axis and Grid drawing
	axisTriad(float4x4::identity, 0.2f, 1.0f);
	xzSquareGrid(-10, 10, 0.0f, 1.0f, colors::Gray);
	App->debugDraw->Draw(App->camera->view, App->camera->proj, SCREEN_WIDTH, SCREEN_HEIGHT);

	// This part is for drawing the triangle 
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(float) * 3 * 6) /*buffer offset*/);
	
	// This part if or using transform in shaders

	glUseProgram(program);
	glUniformMatrix4fv(0, 1, GL_TRUE, & App->camera->model[0][0]);
	glUniformMatrix4fv(1, 1, GL_TRUE, & App->camera->view[0][0]);
	glUniformMatrix4fv(2, 1, GL_TRUE, & App->camera->proj[0][0]);

		
	glDrawArrays(GL_TRIANGLES, 0, 3*2);


	return UPDATE_CONTINUE;
}
