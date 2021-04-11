#pragma once

#include "Debris.h"
#include "Gun.h"
#include "Player.h"

#include <flare/Flare_core.h>

namespace Game {

	using namespace Flare;

	class Game_core : public Flare_core
	{

	public:
		Game_core(int windowWidth, int windowHeight);

		void initialize() noexcept override;
		void enter_frame() noexcept override;

	private:
		shared_ptr<Text_field> statistics{ make_shared<Text_field>("font/disney.ttf", 64) };
		shared_ptr<Gun> gun{ make_shared<Gun>("texture/gun.png") };
		shared_ptr<Debris> debris{ make_shared<Debris>("texture/Debris.png") };

	};
}
