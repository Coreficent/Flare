#pragma once

#include "flare/Sprite.h"

namespace Benchmark
{
	using namespace Flare;

	class Player : public Sprite
	{

	public:
		Player(string texture_url);

		void enter_frame() noexcept override;

	};
}
