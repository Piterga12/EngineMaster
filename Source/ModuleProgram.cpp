#include "ModuleProgram.h"

#include "Globals.h"
#include "Application.h"

#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include <string>


void ModuleProgram::LoadShaderBinFile() {
	// Clean file on Start

}

void ModuleProgram::LoadShaders() {


	LOG("Shaders loaded in ");
}
unsigned ModuleProgram::CreateProgram(const char* shaderFile, const char* vertexSnippets, const char* fragmentSnippets) {
	LOG("Creating program...");

	// Compile the shaders and delete them at the end
	

	return programId;
}

unsigned ModuleProgram::CreateComputeProgram(const char* shaderFile, const char* computeSnippets) {
	LOG("Creating program...");

	
	return programId;
}

/*bool ModuleProgram::Start() {
	LoadShaders();
	return true;
}*/

void ModuleProgram::DeleteProgram(unsigned int IdProgram) {
	//glDeleteProgram(IdProgram);
}

bool ModuleProgram::CleanUp() {
	//UnloadShaders();
	return true;
}