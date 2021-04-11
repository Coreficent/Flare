#include "Game_core.h"

#include <iostream>

namespace Game {

	using namespace Flare;

	Game_core::Game_core(int window_width, int window_height) :Flare_core{ window_width ,window_height } {}

	void Game_core::initialize() noexcept
	{
		try
		{
			shared_ptr<Sprite> sky{ make_shared<Sprite>("texture/Sky.png") };
			sky->width = this->window_width;
			sky->height = this->window_height;
			this->add_child(sky);

			shared_ptr<Sprite> ground{ make_shared<Sprite>("texture/Ground.png") };
			ground->width = 2000;
			ground->height = 200;
			ground->y = 450;
			this->add_child(ground);

			/* player */
			shared_ptr<Player> player{ make_shared<Player>(this->window_width) };
			player->y = 400;
			this->add_child(player);

			gun->width = 50.0f;
			gun->height = 100.0f;
			gun->y = -100.0f;
			player->add_child(gun);

			shared_ptr<Sprite> base{ make_shared<Sprite>("texture/player.png") };
			base->width = 300;
			base->height = 200;
			player->add_child(base);

			this->statistics->text = "statistics";
			this->statistics->x = -400.0f;
			this->statistics->y = -200.0f;
			this->statistics->scale_y = 2.0f;
			this->add_child(statistics);
		}
		catch (...)
		{
			printf("unable to initialize game core");
		}

	}
	void Game_core::enter_frame() noexcept
	{
		Sprite::enter_frame();

		if (Key::is_down(SDL_BUTTON_LEFT))
		{
			shared_ptr<Sprite> bullet{ make_shared<Sprite>("texture/bullet.png") };
			bullet->width = 35;
			bullet->height = 35;
			bullet->x = gun->global_x();
			bullet->y = gun->global_y();

			this->add_child(bullet);
		}

		string delimiter{ " " };
		this->statistics->text = "fps:" + delimiter + to_string(static_cast <int>(this->frame_manager.frames_per_second) + 1) + "\n" + "object:" + delimiter + to_string(this->child_count() + this->total_child_count());
	}
}