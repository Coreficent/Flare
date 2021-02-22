#include "display_object.h"
#include "QuadBatch.h"


Display_object::Display_object(GLuint texture_id)
	:texture_id{texture_id}
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
}

void Display_object::set_y(float value)
{
	this->x = value;
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

void Display_object::render(Dove::Glyph& glyph) const
{
	Dove::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	//printf("%02X\n", glyph.topLeft.color.a);

	glyph.topLeft.color = color;
	glyph.topLeft.setPosition(this->x, this->y+this->height);
	glyph.topLeft.setUV(this->u_start, this->v_end);

	glyph.bottomLeft.color = color;
	glyph.bottomLeft.setPosition(this->x, this->y);
	glyph.bottomLeft.setUV(this->u_start, this->v_start);

	glyph.bottomRight.color = color;
	glyph.bottomRight.setPosition(this->x + this->width, this->y);
	glyph.bottomRight.setUV(this->u_end, this->v_start);

	glyph.topRight.color = color;
	glyph.topRight.setPosition(this->x + this->width, this->y + this->height);
	glyph.topRight.setUV(this->u_end, this->v_end);

	glyph.texture = this->texture_id;

	
}

