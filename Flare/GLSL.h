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
	void linkShader() const;
	void addAttribute(const string& attributeName);

	void use() const;
	void unuse() const;

	GLuint getUniform(const string& uniformName);
private:
	

	GLuint programID;
	GLuint vertexShaderID;
	GLuint fragmentShaderID;

	int attributeCount;

	void compileSource(const string& sourcePath, GLuint shaderID) const;
};

