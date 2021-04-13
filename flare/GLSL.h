#pragma once

#include <gl/glew.h>
#include <string>

namespace Flare
{
	class GLSL
	{

	public:
		GLSL() noexcept;

		void compile_shader(const std::string& vertex_shader_path, const std::string& fragment_shader_path);
		void link_shader() const;
		void add_attribute(const std::string& attribute_name) noexcept;

		void use() const noexcept;
		void unuse() const noexcept;

		GLint get_uniform(const std::string& uniform_name) const;

	private:
		GLuint program_id;
		GLuint vertex_shader_id;
		GLuint fragment_shader_id;

		int attribute_count;

		void compile_source(const std::string& source_path, GLuint shaderID) const;
	};
}
