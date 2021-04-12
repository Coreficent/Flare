#include "Bullet.h"
#include "Gun.h"

#include <flare/Key.h>

namespace Game
{
	Gun::Gun(shared_ptr<Sprite> spawn_layer) : Spawner{ spawn_layer }
	{
		this->gun_graphics->width = 50.0f;
		this->gun_graphics->height = 100.0f;
		this->gun_graphics->y = -100.0f;
		this->add_child(this->gun_graphics);
	}

	void Gun::enter_frame()
	{
		Spawner::enter_frame();

		// avoid concurrent modification
		auto children = this->spawn_layer->children;
		for (auto& bullet : children)
		{
			if (length(vec2{ bullet->global_x(), bullet->global_y() }) > 2000.0f)
			{
				this->spawn_layer->remove_child(bullet);
			}
		}

		if (Key::is_down(SDL_BUTTON_LEFT))
		{
			if (this->frame % this->cool_down == 0)
			{
				shared_ptr<Bullet> bullet{ make_shared<Bullet>("texture/Bullet.png", 1'000) };
				bullet->width = 35;
				bullet->height = 35;
				bullet->x = this->gun_graphics->global_x();
				bullet->y = this->gun_graphics->global_y();
				bullet->speed_x = 0.0f;
				bullet->speed_y = -15.0f;

				this->spawn_layer->add_child(bullet);
			}
		}
	}
}
