#pragma once

#include "Spawner.h"

namespace Game
{
	using namespace Flare;

	class Debris_spawner : public Spawner
	{

	public:
		Debris_spawner() noexcept;
		Debris_spawner(shared_ptr<Sprite> spawn_layer) noexcept;

		void enter_frame() noexcept override;
	};
}