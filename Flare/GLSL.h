#pragma once
#include <string>
#include <gl/glew.h>

using namespace std;

class GLSL
{
public:
	GLSL();
	~GLSL();

	void compileShader(const string& vertexShaderPath, const string& fragmentShaderPath);
	void linkShader();
	void addAttribute(const string& attributeName);

	void use();
	void unuse();


private:
	int attributeCount;
	void compileSource(const string& sourcePath, GLuint shaderID);



	GLuint programID;
	GLuint vertexShaderID;
	GLuint fragmentShaderID;
};

