#include "Debris.h"
#include "Outer_space.h"

namespace Game
{
	Outer_space::Outer_space() noexcept
	{

	}

	void Outer_space::enter_frame() noexcept
	{
		Sprite::enter_frame();

		shared_ptr<Debris> debris{ make_shared<Debris>("texture/Debris.png") };
		debris->width = 100;
		debris->height = 100;
		this->add_child(debris);
	}
}
