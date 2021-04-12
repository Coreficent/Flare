#pragma once

#include "Bullet.h"
#include "Cannon.h"
#include "Debris.h"
#include "Outer_space.h"
#include "Gun.h"
#include "Player.h"

#include <flare/Flare_core.h>
#include <set>

namespace Game {

	using namespace Flare;

	class Game_core : public Flare_core
	{

	public:
		Game_core(int window_width, int window_height);

		void initialize() override;
		void enter_frame() override;

	private:
		shared_ptr<Sprite> static_layer{ make_shared<Sprite>() };
		shared_ptr<Sprite> interactive_layer{ make_shared<Sprite>() };
		shared_ptr<Sprite> interface_layer{ make_shared<Sprite>() };
		shared_ptr<Text_field> statistics{ make_shared<Text_field>("font/disney.ttf", 64) };
		shared_ptr<Sprite> bullet_layer{ make_shared<Sprite>() };
		shared_ptr<Outer_space> debris_layer{ make_shared<Outer_space>(window_width,window_height) };

		shared_ptr<Gun> gun{};
		shared_ptr<Sprite> base{ make_shared<Sprite>("texture/Player.png") };
		shared_ptr<Cannon> cannon_left{};
		shared_ptr<Cannon> cannon_right{};

		Sound hit_sound{ "sound/Water.wav" };
		Sound explode_sound{ "sound/Pop.wav" };
		int score{ 0 };
	};
}
