#pragma once

#include "Module.h"
#include "Globals.h"

class ModuleProgram : public Module {
public:
	//bool Start() override;
	bool CleanUp() override;

	void LoadShaderBinFile();
	void LoadShaders();
	unsigned CreateProgram(const char* shaderFile, const char* vertexSnippets = "vertex", const char* fragmentSnippets = "fragment");
	unsigned CreateComputeProgram(const char* shaderFile, const char* computeSnippets = "compute");
	void DeleteProgram(unsigned int idProgram);

public:
	const char* filePath = "Library/shadersBin";
	int programId = 0;
	// shaders
	
};