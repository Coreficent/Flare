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

		this->progress += 0.0001f;

		if (this->progress > 1.0f) {
			this->progress = 1.0f;
		}

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
			const float size{ (this->progress * 450.0f + 50.0f) * (50 + rand() % 50) / 100 };
			debris->width = size;
			debris->height = size;
			debris->x = (rand() % this->window_width - this->window_width / 2) * 8 / 10;
			debris->y = -this->window_height;
			this->add_child(debris);
		}
	}
}
