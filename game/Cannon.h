#pragma once

#include "Spawner.h"

namespace Game
{
	using namespace Flare;

	class Cannon : public Spawner
	{

	public:
		Cannon(shared_ptr<Sprite> spawn_layer, int windiws_width, int windows_height);
		void enter_frame() override;

	private:
		float calculate_radian(float x1, float y1, float x2, float y2) noexcept;

		shared_ptr<Sprite> cannon_graphics{ make_shared<Sprite>("texture/Cannon.png") };
		int cool_down{30};

		int windiws_width{};
		int windows_height{};
	};
}