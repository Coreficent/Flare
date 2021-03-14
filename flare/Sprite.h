#pragma once

#include "Matrix.h"
#include "Point.h"
#include "Renderer.h"

#include <gl/glew.h>

namespace Flare::Display
{
	class Sprite
	{
	public:
		Sprite() noexcept;

		float get_x() const noexcept;
		float get_y() const noexcept;
		float get_width() const noexcept;
		float get_height() const noexcept;
		GLuint get_texture_id() const noexcept;

		void set_x(float value) noexcept;
		void set_y(float value) noexcept;
		void set_width(float value) noexcept;
		void set_height(float value) noexcept;
		void set_texture_id(GLuint value) noexcept;

		void scale_x(float value) noexcept;
		void scale_y(float value) noexcept;
		void scale(float value) noexcept;
		void rotate(float value) noexcept;

		void render() const;

		void buffer(Renderer& renderer);

		Vial<Vertex>* dest{ nullptr };

	private:
		Matrix matrix{};

		Color color{255,255,255 ,255};

		GLuint texture_id{0};

		float x{0.0f};
		float y{0.0f};
		float width{0.0f};
		float height{0.0f};
		float u_start{0.0f};
		float u_end{1.0f};
		float v_start{0.0f};
		float v_end{1.0f};

		Point locate_vertex(float x, float y) const;
	};
}
