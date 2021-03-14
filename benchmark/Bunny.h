#pragma once

#include "flare/Sprite.h"

namespace Benchmark::Display
{
	using namespace Flare::Display;

	class Bunny : public Sprite
	{
	public:
		virtual void enter_frame() noexcept override;

		float speed_x{ rand() % 50 / 10.f };
		float speed_y{ rand() % 50 / 10.f - 2.5f };

	private:
		float gravity{ 0.5f };
		float minimum_x = { 0.0f };
		float maximum_x = { 500.0f };
		float minimum_y = { 0.0f };
		float maximum_y = { 500.0f };
	};
}
