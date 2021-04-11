#include "Gun.h"
#include "Player.h"

namespace Game
{
	Player::Player(Key& key, int window_width) : Sprite{}, key{ key }, window_width{ window_width }
	{
		shared_ptr<Gun> gun{ make_shared<Gun>("texture/gun.png", this->key) };
		gun->width = 50.0f;
		gun->height = 100.0f;
		gun->y = -100.0f;
		this->add_child(gun);

		shared_ptr<Sprite> player{ make_shared<Sprite>("texture/player.png") };
		player->width = 300;
		player->height = 200;
		this->add_child(player);
	}

	void Player::enter_frame() noexcept
	{
		Sprite::enter_frame();

		try
		{
			const int effective_width{ this->window_width * 8 / 10 / 2 };

			if (this->key.input_manager.keyPressed(SDLK_LEFT))
			{
				if (this->x > -effective_width)
				{
					this->x += -this->move_speed;
				}
			}
			if (this->key.input_manager.keyPressed(SDLK_RIGHT))
			{
				if (this->x < effective_width) {
					this->x += this->move_speed;
				}
			}
		}
		catch (...)
		{
			printf("error processing key input in player");
		}
	}
}
