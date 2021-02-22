#include "Display.h"
#include "Renderer.h"
#include <glm/gtc/matrix_transform.inl>
#include "Point.h"
#include "mathematics.h"
#include "Core.h"

namespace Flare
{
	Display::Display()
	{
	}


	Display::~Display()
	{
	}

	float Display::get_x() const
	{
		return this->x;
	}

	float Display::get_y() const
	{
		return this->y;
	}

	float Display::get_width() const
	{
		return this->width;
	}

	float Display::get_height() const
	{
		return this->height;
	}

	GLuint Display::get_texture_id() const
	{
		return this->texture_id;
	}

	void Display::set_x(float value)
	{
		this->x = value;
		this->matrix.x = value;
	}

	void Display::set_y(float value)
	{
		this->y = value;
		this->matrix.y = value;
	}

	void Display::set_width(float value)
	{
		this->width = value;
	}

	void Display::set_height(float value)
	{
		this->height = value;
	}

	void Display::set_texture_id(GLuint value)
	{
		this->texture_id = value;
	}

	void Display::scale_x(float value)
	{
		this->matrix.a *= value;
		this->matrix.c *= value;
		this->matrix.x *= value;
	}

	void Display::scale_y(float value)
	{
		this->matrix.b *= value;
		this->matrix.d *= value;
		this->matrix.y *= value;
	}

	void Display::scale(float value)
	{
		this->scale_x(value);
		this->scale_y(value);
	}

	void Display::rotate(float value)
	{
		auto sine = sin(value);
		auto cosine = cos(value);
		auto a = this->matrix.a;
		auto b = this->matrix.b;
		auto c = this->matrix.c;
		auto d = this->matrix.d;
		auto x = this->matrix.x;
		auto y = this->matrix.y;
		this->matrix.a = a * cosine - b * sine;
		this->matrix.b = a * sine + b * cosine;
		this->matrix.c = c * cosine - d * sine;
		this->matrix.d = c * sine + d * cosine;
		this->matrix.x = x * cosine - y * sine;
		this->matrix.y = x * sine + y * cosine;
	}

	void Display::render() const
	{
		/*
		auto& glyph = Core::core->renderer.next_glyph();

		auto top_left = this->locate_vertex(0.0f, 0.0f);
		auto top_right = this->locate_vertex(this->width, 0.0f);
		auto down_left = this->locate_vertex(0.0f, this->height);
		auto down_right = this->locate_vertex(this->width, this->height);

		glyph.top_left.color = this->color;
		glyph.top_left.setPosition(top_left.x, top_left.y);
		glyph.top_left.setUV(this->u_start, this->v_start);

		glyph.top_right.color = this->color;
		glyph.top_right.setPosition(top_right.x, top_right.y);
		glyph.top_right.setUV(this->u_end, this->v_start);

		glyph.down_left.color = this->color;
		glyph.down_left.setPosition(down_left.x, down_left.y);
		glyph.down_left.setUV(this->u_start, this->v_end);

		glyph.down_right.color = this->color;
		glyph.down_right.setPosition(down_right.x, down_right.y);
		glyph.down_right.setUV(this->u_end, this->v_end);

		glyph.texture = this->texture_id;

		*/

		// 85 fps to 55 fps
		//Core::core->renderer.hash[this->texture_id];


		auto top_left = this->locate_vertex(0.0f, 0.0f);
		auto top_right = this->locate_vertex(this->width, 0.0f);
		auto down_left = this->locate_vertex(0.0f, this->height);
		auto down_right = this->locate_vertex(this->width, this->height);

		auto& vertex1 = this->dest->next();
		vertex1.color = this->color;
		vertex1.setPosition(top_left.x, top_left.y);
		vertex1.setUV(this->u_start, this->v_start);

		auto& vertex2 = this->dest->next();
		vertex2.color = this->color;
		vertex2.setPosition(top_right.x, top_right.y);
		vertex2.setUV(this->u_end, this->v_start);

		auto& vertex3 = this->dest->next();
		vertex3.color = this->color;
		vertex3.setPosition(down_left.x, down_left.y);
		vertex3.setUV(this->u_start, this->v_end);

		auto& vertex4 = this->dest->next();
		vertex4.color = this->color;
		vertex4.setPosition(down_left.x, down_left.y);
		vertex4.setUV(this->u_start, this->v_end);

		auto& vertex5 = this->dest->next();
		vertex5.color = this->color;
		vertex5.setPosition(top_right.x, top_right.y);
		vertex5.setUV(this->u_end, this->v_start);

		auto& vertex6 = this->dest->next();
		vertex6.color = this->color;
		vertex6.setPosition(down_right.x, down_right.y);
		vertex6.setUV(this->u_end, this->v_end);
	}

	Point Display::locate_vertex(float x, float y) const
	{
		return Point{x * this->matrix.a + y * this->matrix.c + this->matrix.x,x * this->matrix.b + y * this->matrix.d + this->matrix.y};
	}
}
