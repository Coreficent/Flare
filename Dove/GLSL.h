#pragma once
#include <string>
#include <gl/glew.h>


namespace Dove
{
	class GLSL
	{
	public:
		GLSL();
		~GLSL();

		void compileShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		void linkShader() const;
		void addAttribute(const std::string& attributeName);

		void use() const;
		void unuse() const;

		GLint getUniform(const std::string& uniformName) const;
	private:


		GLuint programID;
		GLuint vertexShaderID;
		GLuint fragmentShaderID;

		int attributeCount;

		void compileSource(const std::string& sourcePath, GLuint shaderID) const;
	};
}
