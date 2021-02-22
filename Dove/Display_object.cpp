#include "display_object.h"
#include "QuadBatch.h"
#include <glm/gtc/matrix_transform.inl>
#include "Point.h"

namespace Dove
{
	Display_object::Display_object(GLuint texture_id)
		: texture_id{texture_id}
	{
	}


	Display_object::~Display_object()
	{
	}

	float Display_object::get_x() const
	{
		return this->x;
	}

	float Display_object::get_y() const
	{
		return this->y;
	}

	float Display_object::get_width() const
	{
		return this->width;
	}

	float Display_object::get_height() const
	{
		return this->height;
	}

	GLuint Display_object::get_texture_id() const
	{
		return this->texture_id;
	}

	void Display_object::set_x(float value)
	{
		this->x = value;
		this->matrix.x = value;
	}

	void Display_object::set_y(float value)
	{
		this->y = value;
		this->matrix.y = value;
	}

	void Display_object::set_width(float value)
	{
		this->width = value;
	}

	void Display_object::set_height(float value)
	{
		this->height = value;
	}

	void Display_object::set_texture_id(GLuint value)
	{
		this->texture_id = value;
	}

	void Display_object::scale_x(float value)
	{
		this->matrix.a *= value;
		this->matrix.c *= value;
		this->matrix.x *= value;
	}

	void Display_object::scale_y(float value)
	{
		this->matrix.b *= value;
		this->matrix.d *= value;
		this->matrix.y *= value;
	}

	void Display_object::scale(float value)
	{
		this->scale_x(value);
		this->scale_y(value);
	}

	void Display_object::render(Glyph& glyph) const
	{

		auto top_left = this->locate_vertex(0.0f, 0.0f);
		auto top_right = this->locate_vertex(this->width,0.0f);
		auto down_left = this->locate_vertex(0.0f,this->height);
		auto down_right = this->locate_vertex(this->width,this->height);

		glyph.top_left.color = this->color;
		glyph.top_left.setPosition(top_left.x,top_left.y);
		glyph.top_left.setUV(this->u_start, this->v_start);

		glyph.top_right.color = this->color;
		glyph.top_right.setPosition(top_right.x, top_right.y);
		glyph.top_right.setUV(this->u_end, this->v_start);

		glyph.down_left.color = this->color;
		glyph.down_left.setPosition(down_left.x,down_left.y);
		glyph.down_left.setUV(this->u_start, this->v_end);

		glyph.down_right.color = this->color;
		glyph.down_right.setPosition(down_right.x, down_right.y);
		glyph.down_right.setUV(this->u_end, this->v_end);

		glyph.texture = this->texture_id;
	}
	
	Point Display_object::locate_vertex(float x, float y) const
	{
		return Point{ x*this->matrix.a + y*this->matrix.c + this->matrix.x,x*this->matrix.b + y*this->matrix.d + this->matrix.y };
	}

}
