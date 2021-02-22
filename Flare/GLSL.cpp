#include <fstream>

#include "GLSL.h"
#include "error.h"

using namespace std;

GLSL::GLSL() :programID { 0 }, vertexShaderID{ 0 }, fragmentShaderID{ 0 },attributeCount { 0 }
{
}


GLSL::~GLSL()
{
}

void GLSL::compileShader(const string & vertexShaderPath, const string & fragmentShaderPath)
{
	this->programID = glCreateProgram();
	this->vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if(!this->vertexShaderID)
	{
		fatalError("vertex shader failed");
	}

	this->fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (!this->vertexShaderID)
	{
		fatalError("fragment shader failed");
	}

	this->compileSource(vertexShaderPath, this->vertexShaderID);
	this->compileSource(fragmentShaderPath, this->fragmentShaderID);
}

void GLSL::linkShader() const
{
	glAttachShader(this->programID, this->vertexShaderID);
	glAttachShader(this->programID, this->fragmentShaderID);

	glLinkProgram(this->programID);

	GLint isLinked;
	glGetProgramiv(this->programID, GL_LINK_STATUS, &isLinked);
	if(isLinked == GL_FALSE)
	{
		glDeleteProgram(this->programID);
		glDeleteShader(this->vertexShaderID);
		glDeleteShader(this->fragmentShaderID);
		
		fatalError("link failed");

		return;
	}

	glDetachShader(this->programID, this->vertexShaderID);
	glDetachShader(this->programID, this->fragmentShaderID);
	glDeleteShader(this->vertexShaderID);
	glDeleteShader(this->fragmentShaderID);
}


void GLSL::compileSource(const string& sourcePath, GLuint shaderID) const
{

	ifstream vertexFile(sourcePath);
	if (vertexFile.fail())
	{
		fatalError("failed to open vertex shader");
	}

	string fileContent{ "" };
	string line{ "" };

	while (getline(vertexFile, line))
	{
		fileContent += line + "\n";
	}

	vertexFile.close();
	auto poi = fileContent.c_str();
	glShaderSource(shaderID, 1, &poi, nullptr);

	glCompileShader(shaderID);

	GLint success;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE)
	{
		glDeleteShader(shaderID);
		fatalError("shader" + sourcePath + "compilation failed");
	}
}

void GLSL::addAttribute(const string& attributeName)
{
	glBindAttribLocation(this->programID, this->attributeCount++, attributeName.c_str());
}

void GLSL::use() const
{
	glUseProgram(this->programID);
	for (auto i = 0;i<this->attributeCount;++i)
	{
		glEnableVertexAttribArray(i);
	}
}

void GLSL::unuse () const
{
	glUseProgram(0);
	for (auto i = 0; i<this->attributeCount; ++i)
	{
		glDisableVertexAttribArray(i);
	}
}

GLuint GLSL::getUniform(const string& uniformName)
{
	GLuint location = glGetUniformLocation(this->programID, uniformName.c_str());
	if(location == GL_INVALID_INDEX)
	{
		fatalError("uniform name not found");
	}

	return location;
}