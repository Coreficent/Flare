#pragma once

#include <flare/Sprite.h>

namespace Benchmark
{
	using namespace Flare;

	class Bunny : public Sprite
	{
	public:
		Bunny(string texture_url);

		virtual void enter_frame() noexcept override;

		float speed_x{ rand() % 50 / 10.f };
		float speed_y{ rand() % 50 / 10.f - 2.5f };
		float gravity{ 0.5f };
		float minimum_x{ -100.0f };
		float maximum_x{ 100.0f };
		float minimum_y{ -100.0f };
		float maximum_y{ 100.0f };
	};
}
