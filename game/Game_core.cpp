#include "Bullet.h"
#include "Cannon.h"
#include "Outer_space.h"
#include "Game_core.h"

#include <iostream>
#include <game/Spawner.h>

namespace Game {

	using namespace Flare;

	Game_core::Game_core(int window_width, int window_height) :Flare_core{ window_width ,window_height } {}

	void Game_core::initialize()
	{
		/* static layer */
		this->add_child(this->static_layer);

		shared_ptr<Sprite> sky{ make_shared<Sprite>("texture/Sky.png") };
		sky->width = 1.0f * this->window_width;
		sky->height = 1.0f * this->window_height;
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

		this->gun = make_shared<Gun>(this->bullet_layer, this->window_width, this->window_height);
		player->add_child(this->gun);


		this->base->width = 300.0f;
		this->base->height = 200.0f;
		player->add_child(this->base);

		this->cannon_left = make_shared<Cannon>(this->bullet_layer, this->window_width, this->window_height);
		this->cannon_left->x = -150.0f;
		this->cannon_left->y = 75.0f;
		player->add_child(this->cannon_left);

		this->cannon_right = make_shared<Cannon>(this->bullet_layer, this->window_width, this->window_height);
		this->cannon_right->x = 150.0f;
		this->cannon_right->y = 75.0f;
		player->add_child(this->cannon_right);

		this->interactive_layer->add_child(this->debris_layer);

		/* user interface layer */
		this->add_child(this->interface_layer);

		this->statistics->text = "statistics";
		const float border{ 25.0f };
		this->statistics->x = -this->window_width / 2 + border;
		this->statistics->y = -this->window_height / 2 + border;
		this->statistics->scale_y = 2.0f;
		this->interface_layer->add_child(statistics);


	}
	void Game_core::enter_frame()
	{
		Sprite::enter_frame();

		auto bullet_children = this->bullet_layer->children;
		auto debris_children = this->debris_layer->children;

		for (auto& debris_sprite : debris_children)
		{
			if (this->base->hit_test_object(*debris_sprite))
			{
				this->debris_layer->remove_child(debris_sprite);
				this->score += 25;

				this->explode_sound.play();
			}
			else
			{
				for (auto& bullet_sprite : bullet_children)
				{
					if (bullet_sprite->hit_test_object(*debris_sprite))
					{
						this->bullet_layer->remove_child(bullet_sprite);
						this->hit_sound.play();

						auto& debris = static_cast<Debris&>(*debris_sprite);
						const auto& bullet = static_cast<Bullet&>(*bullet_sprite);
						debris.mass -= bullet.damage;
						this->score += 5;

						if (debris.mass < 50.0f)
						{
							this->debris_layer->remove_child(debris_sprite);
							this->score += 15;

							this->explode_sound.play();
						}
					}
				}
			}
		}

		this->gun->cool_down = 5 + 250 * 1'00 / (this->score + 1);
		this->cannon_left->cool_down = this->cannon_right->cool_down = 10 + 125 * 1'00 / (this->score + 1);

		const int score_maximum{ 99'999 };
		if (this->score > score_maximum) {
			this->score = score_maximum;
		}

		string delimiter{ " " };
		this->statistics->text = "";
		this->statistics->text += "fps:" + delimiter + to_string(static_cast <int>(this->frame_manager.frames_per_second) + 1) + "\n";
		this->statistics->text += "object:" + delimiter + to_string(this->total_child_count()) + "\n";
		this->statistics->text += "draw call:" + delimiter + to_string(this->renderer.draw_call_count) + "\n";
		this->statistics->text += "score:" + delimiter + to_string(this->score) + "\n";
	}
}
