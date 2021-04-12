#pragma once

#include "Spawner.h"

namespace Game
{
	using namespace Flare;

	class Outer_space : public Sprite
	{

	public:
		Outer_space() noexcept;

		void enter_frame() noexcept override;

	private:
		int spawn_chance_per_frame{1};
	};
}