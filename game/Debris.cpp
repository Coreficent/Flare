#include "Debris.h"

namespace Game
{
	Debris::Debris(string texture_url) : Sprite{ texture_url }
	{

	}

	void Debris::enter_frame() noexcept
	{
		this->y += this->speed;
	}
}
