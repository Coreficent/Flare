#include "Bullet.h"
#include "Cannon.h"

#include <flare/Key.h>
#include <iostream>

namespace Game
{
	Cannon::Cannon(shared_ptr<Sprite> spawn_layer, int windiws_width, int windows_height) : Spawner{ spawn_layer }, windiws_width{ windiws_width }, windows_height{ windows_height }
	{
		this->cannon_graphics->width = 50.0f;
		this->cannon_graphics->height = 50.0f;
		this->add_child(this->cannon_graphics);
	}

	void Cannon::enter_frame()
	{
		Spawner::enter_frame();

		// cout << calculate_radian(this->cannon_graphics->global_x(), this->cannon_graphics->global_y(), Key::mouse_position.x - this->windiws_width / 2, Key::mouse_position.y - this->windows_height / 2) << endl;

		const float radian{ calculate_radian(this->cannon_graphics->global_x(), this->cannon_graphics->global_y(), Key::mouse_position.x - this->windiws_width / 2, Key::mouse_position.y - this->windows_height / 2) };
		this->cannon_graphics->rotation = degrees(radian);

		//cout << ( Key::mouse_position.x) << endl;
		// avoid concurrent modification
		auto children = this->spawn_layer->children;
		for (auto& bullet : children)
		{
			if (abs(bullet->global_x()) > this->windiws_width / 2 || abs(bullet->global_y()) > this->windows_height / 2)
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
				bullet->x = this->cannon_graphics->global_x();
				bullet->y = this->cannon_graphics->global_y();
				constexpr float speed{ 10.0f };
				bullet->speed_x = cos(radian) * speed;
				bullet->speed_y = sin(radian) * speed;

				this->spawn_layer->add_child(bullet);

				this->bullet_sound.play();
			}
		}
	}

	float Cannon::calculate_radian(float x1, float y1, float x2, float y2) noexcept
	{
		const float dx{ x2 - x1 };
		const float dy{ y2 - y1 };

		return atan2(dy, dx);
	}
}
