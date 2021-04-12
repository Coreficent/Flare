#include "Player.h"

namespace Game
{
	Player::Player(int window_width) : Sprite{}, window_width{ window_width }
	{
		
	}

	void Player::enter_frame()
	{
		Sprite::enter_frame();

		try
		{
			const int effective_width{ this->window_width * 8 / 10 / 2 };

			if (Key::is_down(SDLK_LEFT))
			{
				if (this->x > -effective_width)
				{
					this->x += -this->move_speed;
				}
			}
			if (Key::is_down(SDLK_RIGHT))
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
