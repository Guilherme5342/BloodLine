#include "OGLShader.h"
#include "../../Common/Assets.h"
#include <iostream>

using namespace NCL;
using namespace NCL::Rendering;

GLuint shaderTypes[ShaderStages::SHADER_MAX] = {
	GL_VERTEX_SHADER,
	GL_FRAGMENT_SHADER,
	GL_GEOMETRY_SHADER,
	GL_TESS_CONTROL_SHADER,
	GL_TESS_EVALUATION_SHADER
};

string ShaderNames[ShaderStages::SHADER_MAX] = {
	"Vertex",
	"Fragment",
	"Geometry",
	"Tess. Control",
	"Tess. Eval"
};

OGLShader::OGLShader(const string& vertex, const string& fragment, const string& geometry, const string& domain, const string& hull) :
	ShaderBase(vertex, fragment, geometry, domain, hull) {
	ReloadShader();
}

OGLShader::~OGLShader()	{
	DeleteIDs();
}

void OGLShader::ReloadShader() {
	DeleteIDs();
	programID = glCreateProgram();
	string fileContents = "";
	for (int i = 0; i < ShaderStages::SHADER_MAX; ++i) {
		if (!shaderFiles[i].empty()) {
			if (Assets::ReadTextFile(Assets::SHADERDIR + shaderFiles[i], fileContents)) {
				shaderIDs[i] = glCreateShader(shaderTypes[i]);

				std::cout << "Reading " << ShaderNames[i] << " shader " << shaderFiles[i] << std::endl;

				const char* stringData	 = fileContents.c_str();
				int			stringLength = fileContents.length();
				glShaderSource(shaderIDs[i], 1, &stringData, &stringLength);
				glCompileShader(shaderIDs[i]);

				glGetShaderiv(shaderIDs[i], GL_COMPILE_STATUS, &shaderValid[i]);
		
				if (shaderValid[i] != GL_TRUE) {
					std::cout << ShaderNames[i] << " shader " << " has failed!" << std::endl;
				}
				else {
					glAttachShader(programID, shaderIDs[i]);
				}
				PrintCompileLog(shaderIDs[i]);
			}
		}
	}	
	glLinkProgram(programID);
	glGetProgramiv(programID, GL_LINK_STATUS, &programValid);

	PrintLinkLog();

	if (programValid != GL_TRUE) {
		std::cout << "This shader has failed!" << std::endl;
	}
	else {
		std::cout << "Shader loaded!" << std::endl;
	}
}

void	OGLShader::DeleteIDs() {
	if (!programID) {
		return;
	}
	for (int i = 0; i < ShaderStages::SHADER_MAX; ++i) {
		if (shaderIDs[i]) {
			glDetachShader(programID, shaderIDs[i]);
			glDeleteShader(shaderIDs[i]);
		}
	}
	glDeleteProgram(programID);
	programID = 0;
}

void	OGLShader::PrintCompileLog(int object) const {
	int logLength = 0;
	glGetShaderiv(object, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength) {
		char* tempData = new char[logLength];
		glGetShaderInfoLog(object, logLength, NULL, tempData);
		std::cout << "Link Log:\n" << tempData << std::endl;
		delete tempData;
	}
}

void	OGLShader::PrintLinkLog() const {
	int logLength = 0;
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &logLength);

	if (logLength) {
		char* tempData = new char[logLength];
		glGetProgramInfoLog(programID, logLength, NULL, tempData);
		std::cout << "Link Log:\n" << tempData << std::endl;
		delete tempData;
	}
}