#pragma once
#include <gl/glew.h>
#include "Matrix.h"
#include "Point.h"
#include "QuadBatch.h"

namespace Dove
{
	class Display_object
	{
	public:
		explicit Display_object(GLuint texture_id);
		~Display_object();

		float get_x() const;
		float get_y() const;
		float get_width() const;
		float get_height() const;
		GLuint get_texture_id() const;

		void set_x(float value);
		void set_y(float value);
		void set_width(float value);
		void set_height(float value);
		void set_texture_id(GLuint value);

		void render(Glyph& glyph) const;

	private:

		Matrix matrix{};

		Color color{ 255,255,255 ,255};

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
