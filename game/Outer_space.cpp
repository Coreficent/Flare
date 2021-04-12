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

		auto children = this->children;
		for (auto& debris : children)
		{
			if (length(vec2{ debris->global_x(), debris->global_y() }) > 2000.0f)
			{
				this->remove_child(debris);
			}
		}

		if (this->spawn_chance_per_frame > rand() % 100)
		{
			shared_ptr<Debris> debris{ make_shared<Debris>("texture/Debris.png") };
			debris->width = 100;
			debris->height = 100;
			this->add_child(debris);
		}
	}
}
