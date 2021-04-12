#include "Bullet.h"
#include "Cannon.h"

#include <flare/Key.h>

namespace Game
{
	Cannon::Cannon(shared_ptr<Sprite> spawn_layer) : Spawner{ spawn_layer }
	{
		this->cannon_graphics->width = 50.0f;
		this->cannon_graphics->height = 50.0f;
		this->add_child(this->cannon_graphics);
	}

	void Cannon::enter_frame()
	{
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
			shared_ptr<Bullet> bullet{ make_shared<Bullet>("texture/Bullet.png", 1'000) };
			bullet->width = 35;
			bullet->height = 35;
			bullet->x = this->cannon_graphics->global_x();
			bullet->y = this->cannon_graphics->global_y();

			this->spawn_layer->add_child(bullet);
		}
	}
}
