#include "Gun.h"

namespace Game
{
	Gun::Gun(string texture_url) : Sprite{ texture_url }
	{
	}

	void Gun::enter_frame() noexcept
	{
		try
		{
			if (Key::input_manager.keyPressed(SDL_BUTTON_LEFT))
			{
				shared_ptr<Sprite> bullet{ make_shared<Sprite>("texture/bullet.png") };
				bullet->width = 35;
				bullet->height = 35;
				bullet->y = -125.0f;
				this->add_child(bullet);
			}
		}
		catch (...)
		{
			printf("error processing key input in gun");
		}
	}
}
