#include "Point.h"
#include "Sprite.h"

#include <iostream>

namespace Flare
{
	Sprite::Sprite() noexcept {}

	vec4 Sprite::get_bound()
	{
		return vec4{ this->x, this->y, this->width , this->height };
	}

	vec4 Sprite::get_uv()
	{
		return vec4{ this->u_start,this->v_start,this->u_end,this->v_end };
	}

	vector<Quad> Sprite::graphics()
	{
		return vector<Quad>{Quad{ texture_id, get_bound(),get_uv() }};
	}

	void Sprite::enter_frame() noexcept
	{

	}

	Point Sprite::locate_vertex(float x, float y) const
	{
		return Point{ x * this->matrix.a + y * this->matrix.c + this->matrix.x,x * this->matrix.b + y * this->matrix.d + this->matrix.y };
	}
}
