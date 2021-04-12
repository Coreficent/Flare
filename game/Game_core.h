#pragma once

#include "Bullet.h"
#include "Debris.h"
#include "Debris_spawner.h"
#include "Gun.h"
#include "Player.h"

#include <flare/Flare_core.h>
#include <set>

namespace Game {

	using namespace Flare;

	class Game_core : public Flare_core
	{

	public:
		Game_core(int windowWidth, int windowHeight);

		void initialize() noexcept override;
		void enter_frame() noexcept override;

	private:
		shared_ptr<Sprite> static_layer{ make_shared<Sprite>() };
		shared_ptr<Sprite> interactive_layer{ make_shared<Sprite>() };
		shared_ptr<Sprite> interface_layer{ make_shared<Sprite>() };
		shared_ptr<Text_field> statistics{ make_shared<Text_field>("font/disney.ttf", 64) };
	};
}
