#pragma once

#include "flare/Key.h"
#include "flare/Sprite.h"

namespace Game
{
	using namespace Flare;

	class Player : public Sprite
	{

	public:
		Player(int window_width);

		void enter_frame() noexcept override;

	private:
		int window_width{};
		float move_speed{ 10.0f };
	};
}
