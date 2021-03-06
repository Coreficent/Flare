#pragma once

#include "Spawner.h"
#include <flare/Sound.h>

namespace Game
{
	using namespace Flare;

	class Gun : public Spawner
	{

	public:
		Gun(shared_ptr<Sprite> spawn_layer, int windiws_width, int windows_height);
		void enter_frame() override;

		int cool_down{ 100 };

	private :
		shared_ptr<Sprite> gun_graphics{ make_shared<Sprite>("texture/Gun.png") };

		Sound bullet_sound{ "sound/Liquid.wav" };

		int windiws_width{};
		int windows_height{};
	};
}