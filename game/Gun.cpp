#include "Bullet.h"
#include "Gun.h"

#include <flare/Key.h>

namespace Game
{
	Gun::Gun(string texture_url, shared_ptr<Sprite> spawn_layer) : Sprite{ texture_url }, spawn_layer{ spawn_layer }
	{

	}

	void Gun::enter_frame() noexcept
	{
		if (Key::is_down(SDL_BUTTON_LEFT))
		{
			shared_ptr<Bullet> bullet{ make_shared<Bullet>("texture/bullet.png", 1'000) };
			bullet->width = 35;
			bullet->height = 35;
			bullet->x = this->global_x();
			bullet->y = this->global_y();

			this->spawn_layer->add_child(bullet);
		}
	}
}
