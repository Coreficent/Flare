#include "Point.h"
#include "Sprite.h"
#include "mathematics.h"
#include <glm/gtc/matrix_transform.inl>

namespace Flare::Display
{
	using namespace glm;

	Sprite::Sprite() noexcept {}

	float Sprite::get_x() const noexcept
	{
		return this->x;
	}

	float Sprite::get_y() const noexcept
	{
		return this->y;
	}

	float Sprite::get_width() const noexcept
	{
		return this->width;
	}

	float Sprite::get_height() const noexcept
	{
		return this->height;
	}

	GLuint Sprite::get_texture_id() const noexcept
	{
		return this->texture_id;
	}

	void Sprite::set_x(float value) noexcept
	{
		this->x = value;
		this->matrix.x = value;
	}

	void Sprite::set_y(float value) noexcept
	{
		this->y = value;
		this->matrix.y = value;
	}

	void Sprite::set_width(float value) noexcept
	{
		this->width = value;
	}

	void Sprite::set_height(float value) noexcept
	{
		this->height = value;
	}

	void Sprite::set_texture_id(GLuint value) noexcept
	{
		this->texture_id = value;
	}

	void Sprite::scale_x(float value) noexcept
	{
		this->matrix.a *= value;
		this->matrix.c *= value;
		this->matrix.x *= value;
	}

	void Sprite::scale_y(float value) noexcept
	{
		this->matrix.b *= value;
		this->matrix.d *= value;
		this->matrix.y *= value;
	}

	void Sprite::scale(float value) noexcept
	{
		this->scale_x(value);
		this->scale_y(value);
	}

	void Sprite::rotate(float value) noexcept
	{
		const auto sine = sin(value);
		const auto cosine = cos(value);
		const auto a = this->matrix.a;
		const auto b = this->matrix.b;
		const auto c = this->matrix.c;
		const auto d = this->matrix.d;
		const auto x = this->matrix.x;
		const auto y = this->matrix.y;

		this->matrix.a = a * cosine - b * sine;
		this->matrix.b = a * sine + b * cosine;
		this->matrix.c = c * cosine - d * sine;
		this->matrix.d = c * sine + d * cosine;
		this->matrix.x = x * cosine - y * sine;
		this->matrix.y = x * sine + y * cosine;
	}

	void Sprite::render() const
	{
		auto top_left = this->locate_vertex(0.0f, 0.0f);
		auto top_right = this->locate_vertex(this->width, 0.0f);
		auto bottom_left = this->locate_vertex(0.0f, this->height);
		auto bottom_right = this->locate_vertex(this->width, this->height);

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
		vertex3.setPosition(bottom_left.x, bottom_left.y);
		vertex3.setUV(this->u_start, this->v_end);

		auto& vertex4 = this->dest->next();
		vertex4.color = this->color;
		vertex4.setPosition(bottom_left.x, bottom_left.y);
		vertex4.setUV(this->u_start, this->v_end);

		auto& vertex5 = this->dest->next();
		vertex5.color = this->color;
		vertex5.setPosition(top_right.x, top_right.y);
		vertex5.setUV(this->u_end, this->v_start);

		auto& vertex6 = this->dest->next();
		vertex6.color = this->color;
		vertex6.setPosition(bottom_right.x, bottom_right.y);
		vertex6.setUV(this->u_end, this->v_end);
	}

	/*void Sprite::buffer(Renderer& renderer)
	{
		const vec4 bound{ this->x, this->y, this->width , this->height };
		const vec4 uv{ this->u_start,this->v_start,this->u_end,this->v_end };
		renderer.draw(bound, uv, get_texture_id(), 0.0f, Color{ 255,255,255,255 });
	}*/

	vec4 Sprite::get_bound()
	{
		return vec4{ this->x, this->y, this->width , this->height };
	}

	vec4 Sprite::get_uv()
	{
		return vec4{ this->u_start,this->v_start,this->u_end,this->v_end };
	}

	Quad Sprite::get_quad()
	{
		return Quad{ texture_id, get_bound(),get_uv() };
	}

	void Sprite::enter_frame() noexcept
	{
	}



	Point Sprite::locate_vertex(float x, float y) const
	{
		return Point{ x * this->matrix.a + y * this->matrix.c + this->matrix.x,x * this->matrix.b + y * this->matrix.d + this->matrix.y };
	}
}
