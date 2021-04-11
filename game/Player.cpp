#include "Player.h"

namespace Game
{
	Player::Player(string texture_url, Key& key, int window_width) : Sprite{ texture_url }, key{ key }, window_width{ window_width }
	{

	}

	void Player::enter_frame() noexcept
	{
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
