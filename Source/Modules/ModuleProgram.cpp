#include "ModuleProgram.h"
#include <fstream>

const std::string ModuleProgram::FOLDER_SHADERS = "shaders/";

ModuleProgram::ModuleProgram()
{
}

ModuleProgram::~ModuleProgram()
{
}

GLuint ModuleProgram::CreateProgramFromShaders(const std::string& vertexShaderName, const std::string& fragmentShaderName)
{
	std::string vertexShaderCode = ReadShaderFile(vertexShaderName);
	std::string fragmentShaderCode = ReadShaderFile(fragmentShaderName);

	GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderCode);
	GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderCode);

	GLuint program = CreateProgram(vertexShader, fragmentShader);

	return program;
}

std::string ModuleProgram::ReadShaderFile(const std::string& shaderName)
{
	std::ifstream file;
	std::string fileContents = "";
	std::string fileLine;

	file.open(FOLDER_SHADERS + shaderName);

	if (file.is_open()) {
		while (std::getline(file, fileLine)) {
			fileContents += fileLine + "\n";
		}
		file.close();
	}

	return fileContents;
}

GLuint ModuleProgram::CompileShader(GLenum shaderType, const std::string& shaderSource)
{
	GLuint shaderID = glCreateShader(shaderType);
	const char* sourceAsChars = shaderSource.c_str();
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
			PERSLOG("Log Info: %s", info);
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
			PERSLOG("Program Log Info: %s", info);
			free(info);
		}
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return programID;
}