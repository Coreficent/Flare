#include "GLSL.h"
#include "error.h"

#include <fstream>

using namespace std;

namespace Flare
{
	GLSL::GLSL() noexcept : program_id{ 0 }, vertex_shader_id{ 0 }, fragment_shader_id{ 0 }, attribute_count{ 0 }
	{
	}

	void GLSL::compile_shader(const string& vertex_shader_path, const string& fragment_shader_path)
	{
		this->program_id = glCreateProgram();
		this->vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
		if (!this->vertex_shader_id)
		{
			output_error("vertex shader failed");
		}

		this->fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
		if (!this->vertex_shader_id)
		{
			output_error("fragment shader failed");
		}

		this->compile_source(vertex_shader_path, this->vertex_shader_id);
		this->compile_source(fragment_shader_path, this->fragment_shader_id);
	}

	void GLSL::link_shader() const
	{
		glAttachShader(this->program_id, this->vertex_shader_id);
		glAttachShader(this->program_id, this->fragment_shader_id);

		glLinkProgram(this->program_id);

		GLint is_linked;
		glGetProgramiv(this->program_id, GL_LINK_STATUS, &is_linked);
		if (is_linked == GL_FALSE)
		{
			glDeleteProgram(this->program_id);
			glDeleteShader(this->vertex_shader_id);
			glDeleteShader(this->fragment_shader_id);

			output_error("link failed");

			return;
		}

		glDetachShader(this->program_id, this->vertex_shader_id);
		glDetachShader(this->program_id, this->fragment_shader_id);
		glDeleteShader(this->vertex_shader_id);
		glDeleteShader(this->fragment_shader_id);
	}


	void GLSL::compile_source(const string& source_path, GLuint shader_id) const
	{
		ifstream vertex_file(source_path);
		if (vertex_file.fail())
		{
			output_error("failed to open vertex shader");
		}

		string file_content{ "" };
		string line{ "" };

		while (getline(vertex_file, line))
		{
			file_content += line + "\n";
		}

		vertex_file.close();
		auto poi = file_content.c_str();
		glShaderSource(shader_id, 1, &poi, nullptr);

		glCompileShader(shader_id);

		GLint success;
		glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);

		if (success == GL_FALSE)
		{
			glDeleteShader(shader_id);
			output_error("shader" + source_path + "compilation failed");
		}
	}

	void GLSL::add_attribute(const string& attribute_name) noexcept
	{
		glBindAttribLocation(this->program_id, this->attribute_count++, attribute_name.c_str());
	}

	void GLSL::use() const noexcept
	{
		glUseProgram(this->program_id);
		for (auto i = 0; i < this->attribute_count; ++i)
		{
			glEnableVertexAttribArray(i);
		}
	}

	void GLSL::unuse() const noexcept
	{
		glUseProgram(0);
		for (auto i = 0; i < this->attribute_count; ++i)
		{
			glDisableVertexAttribArray(i);
		}
	}

	GLint GLSL::get_uniform(const string& uniform_name) const
	{
		const auto location = glGetUniformLocation(this->program_id, uniform_name.c_str());
		if (location == GL_INVALID_INDEX)
		{
			output_error("uniform name not found");
		}

		return location;
	}
}
