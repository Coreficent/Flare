#pragma once

#include "flare/Sprite.h"

namespace Benchmark::Display
{
	using namespace Flare::Display;

	class Bunny : public Sprite
	{
		virtual void enter_frame() noexcept override;
	};
}
