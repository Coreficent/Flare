#include "Debris.h"

namespace Game
{
	Debris::Debris(string texture_url, float mass) : Sprite{ texture_url }, mass{ mass }
	{

	}

	void Debris::enter_frame() noexcept
	{
		this->width = mass;
		this->height = mass;
		this->y += this->speed / this->mass * 10.0f;
	}
}
