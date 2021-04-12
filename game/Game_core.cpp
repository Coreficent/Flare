#include "Bullet.h"
#include "Outer_space.h"
#include "Game_core.h"

#include <iostream>
#include <game/Spawner.h>

namespace Game {

	using namespace Flare;

	Game_core::Game_core(int window_width, int window_height) :Flare_core{ window_width ,window_height } {}

	void Game_core::initialize() noexcept
	{
		try
		{
			/* static layer */
			this->add_child(this->static_layer);

			shared_ptr<Sprite> sky{ make_shared<Sprite>("texture/Sky.png") };
			sky->width = this->window_width;
			sky->height = this->window_height;
			this->static_layer->add_child(sky);

			shared_ptr<Sprite> ground{ make_shared<Sprite>("texture/Ground.png") };
			ground->width = 2000;
			ground->height = 200;
			ground->y = 450;
			this->static_layer->add_child(ground);


			/* interactive layer */
			this->add_child(this->interactive_layer);

			shared_ptr<Player> player{ make_shared<Player>(this->window_width) };
			player->y = 400;
			this->interactive_layer->add_child(player);


			this->interactive_layer->add_child(this->bullet_layer);

			shared_ptr<Gun> gun{ make_shared<Gun>(this->bullet_layer) };
			player->add_child(gun);

			shared_ptr<Gun> gun2{ make_shared<Gun>(this->bullet_layer) };
			gun2->x = 100.0f;
			player->add_child(gun2);

			shared_ptr<Sprite> base{ make_shared<Sprite>("texture/Player.png") };
			base->width = 300;
			base->height = 200;
			player->add_child(base);


			this->interactive_layer->add_child(this->debrist_layer);



			/* user interface layer */
			this->add_child(this->interface_layer);

			this->statistics->text = "statistics";
			this->statistics->x = -400.0f;
			this->statistics->y = -200.0f;
			this->statistics->scale_y = 2.0f;
			this->interface_layer->add_child(statistics);


		}
		catch (...)
		{
			printf("unable to initialize game core");
		}

	}
	void Game_core::enter_frame() noexcept
	{
		Sprite::enter_frame();

		auto bullets = this->bullet_layer->children;
		auto debris = this->debrist_layer->children;

		for (auto& b : bullets)
		{
			for (auto& d : debris)
			{
				if (b->hit_test_object(*d))
				{
					this->bullet_layer->remove_child(b);
					this->debrist_layer->remove_child(d);
				}
			}
		}

		try
		{
			string delimiter{ " " };
			this->statistics->text = "";
			this->statistics->text += "fps:" + delimiter + to_string(static_cast <int>(this->frame_manager.frames_per_second) + 1) + "\n";
			this->statistics->text += "object:" + delimiter + to_string(this->total_child_count()) + "\n";;
			this->statistics->text += "draw call:" + delimiter + to_string(this->renderer.draw_call_count) + "\n";;
		}
		catch (...)
		{
			printf("error encountered during enter frame in game core");
		}
	}
}