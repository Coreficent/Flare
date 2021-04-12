#pragma once

#include "Spawner.h"

namespace Game
{
	using namespace Flare;

	class Outer_space : public Sprite
	{

	public:
		Outer_space(int window_width, int window_height) noexcept;

		void enter_frame() override;

	private:
		int spawn_chance_per_frame{1};
		int window_width{};
		int window_height{};

		float progress{0.0f};
	};
}