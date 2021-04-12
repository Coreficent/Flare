#include "Debris.h"
#include "Outer_space.h"

namespace Game
{
	Outer_space::Outer_space(int window_width, int window_height) noexcept : window_width{ window_width }, window_height{ window_height }
	{

	}

	void Outer_space::enter_frame()
	{
		Sprite::enter_frame();

		auto children = this->children;
		for (auto& debris : children)
		{
			if (length(vec2{ debris->global_x(), debris->global_y() }) > 1.5f * glm::max(this->window_width, this->window_height))
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
