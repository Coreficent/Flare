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

		shared_ptr<Gun> gun{ make_shared<Gun>(this->bullet_layer, this->window_width,this->window_height) };
		player->add_child(gun);

		shared_ptr<Sprite> base{ make_shared<Sprite>("texture/Player.png") };
		base->width = 300;
		base->height = 200;
		player->add_child(base);

		shared_ptr<Cannon> cannon_left{ make_shared<Cannon>(this->bullet_layer, this->window_width, this->window_height) };
		cannon_left->x = -150.0f;
		cannon_left->y = 75.0f;
		player->add_child(cannon_left);

		shared_ptr<Cannon> cannon_right{ make_shared<Cannon>(this->bullet_layer, this->window_width, this->window_height) };
		cannon_right->x = 150.0f;
		cannon_right->y = 75.0f;
		player->add_child(cannon_right);

		this->interactive_layer->add_child(this->debris_layer);

		/* user interface layer */
		this->add_child(this->interface_layer);

		this->statistics->text = "statistics";
		this->statistics->x = -400.0f;
		this->statistics->y = -200.0f;
		this->statistics->scale_y = 2.0f;
		this->interface_layer->add_child(statistics);


	}
	void Game_core::enter_frame()
	{
		Sprite::enter_frame();

		auto bullet_children = this->bullet_layer->children;
		auto debris_children = this->debris_layer->children;

		for (auto& bullet : bullet_children)
		{
			for (auto& debris : debris_children)
			{
				if (bullet->hit_test_object(*debris))
				{
					this->bullet_layer->remove_child(bullet);
					this->hit_sound.play();

					auto& debris_cast = static_cast<Debris&>(*debris);
					debris_cast.mass -= 10.0f;

					this->score += 1;

					if (debris_cast.mass < 50.0f)
					{
						this->debris_layer->remove_child(debris);
						this->score += 10;

						this->explode_sound.play();
					}
				}
			}
		}

		string delimiter{ " " };
		this->statistics->text = "";
		this->statistics->text += "fps:" + delimiter + to_string(static_cast <int>(this->frame_manager.frames_per_second) + 1) + "\n";
		this->statistics->text += "object:" + delimiter + to_string(this->total_child_count()) + "\n";
		this->statistics->text += "draw call:" + delimiter + to_string(this->renderer.draw_call_count) + "\n";
		this->statistics->text += "score:" + delimiter + to_string(this->score) + "\n";
	}
}
