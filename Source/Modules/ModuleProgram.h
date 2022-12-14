#pragma once

#include "Module.h"
#include <string>
#include <GL\glew.h>

class ModuleProgram : public Module
{
public:
	ModuleProgram();
	~ModuleProgram();

	static const std::string s_shaderFolderPath;

	GLuint CreateProgramFromShaders(const std::string& i_vertexShaderName, const std::string& i_fragmentShaderName);

private:
	std::string ReadShaderFile(const std::string& i_fileName);
	GLuint CompileShader(GLenum Type, const std::string& Source);
	GLuint CreateProgram(GLuint vertexShader, GLuint fragmentShader);
};

