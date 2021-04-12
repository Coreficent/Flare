#include "Bullet.h"

namespace Game
{
	Bullet::Bullet(string texture_url, int window_height) : Sprite{ texture_url }, window_height{ window_height }
	{

	}

	void Bullet::enter_frame()
	{
		this->y -= this->speed;
	}
}
