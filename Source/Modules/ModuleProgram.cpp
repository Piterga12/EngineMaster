#include "ModuleProgram.h"

#include <fstream>
#include "..\Application.h"
#include "ModuleEditor.h"

const std::string ModuleProgram::s_shaderFolderPath = "shaders/";

ModuleProgram::ModuleProgram()
{
}

ModuleProgram::~ModuleProgram()
{
}

GLuint ModuleProgram::CreateProgramFromShaders(const std::string& i_vertexShaderName, const std::string& i_fragmentShaderName)
{
	std::string vertexShaderCode = ReadShaderFile(i_vertexShaderName);
	std::string fragmentShaderCode = ReadShaderFile(i_fragmentShaderName);

	GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderCode);
	GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderCode);

	GLuint program = CreateProgram(vertexShader, fragmentShader);

	return program;
}

std::string ModuleProgram::ReadShaderFile(const std::string& i_fileName)
{
	std::ifstream file;
	std::string fileContents = "";
	std::string fileLine;

	file.open(s_shaderFolderPath + i_fileName);

	if (file.is_open()) {
		while (std::getline(file, fileLine)) {
			fileContents += fileLine + "\n";
		}
		file.close();
	}

	return fileContents;
}

GLuint ModuleProgram::CompileShader(GLenum Type, const std::string& Source)
{
	GLuint shaderID = glCreateShader(Type);
	const char* sourceAsChars = Source.c_str();
	glShaderSource(shaderID, 1, &sourceAsChars, 0);
	glCompileShader(shaderID);

	int res = GL_FALSE;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &res);
	if (res == GL_FALSE) {
		int len = 0;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &len);
		if (len > 0) {
			int written = 0;
			char* info = (char*)malloc(len);
			glGetShaderInfoLog(shaderID, len, &written, info);
			free(info);
		}
	}
	return shaderID;
}

GLuint ModuleProgram::CreateProgram(GLuint vertexShader, GLuint fragmentShader)
{
	GLuint programID = glCreateProgram();
	glAttachShader(programID, vertexShader);
	glAttachShader(programID, fragmentShader);
	glLinkProgram(programID);

	int res = GL_FALSE;
	glGetProgramiv(programID, GL_LINK_STATUS, &res);
	if (res == GL_FALSE) {
		int len = 0;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &len);
		if (len > 0)
		{
			int written = 0;
			char* info = (char*)malloc(len);
			glGetProgramInfoLog(programID, len, &written, info);
			free(info);
		}
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return programID;
}
