#pragma once

#include "Spawner.h"

namespace Game
{
	using namespace Flare;

	class Cannon : public Spawner
	{

	public:
		Cannon(shared_ptr<Sprite> spawn_layer);
		void enter_frame() override;

	private:
		shared_ptr<Sprite> cannon_graphics{ make_shared<Sprite>("texture/Cannon.png") };
		int cool_down{30};
	};
}