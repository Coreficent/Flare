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
			if (this->key.input_manager.keyPressed(SDLK_LEFT))
			{
				this->x += -this->move_speed;
			}
			if (this->key.input_manager.keyPressed(SDLK_RIGHT))
			{
				this->x += this->move_speed;
			}
		}
		catch (...)
		{
			printf("error processing key input in player");
		}
	}
}
