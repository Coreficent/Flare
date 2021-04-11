#include "Game_core.h"

#include <iostream>

namespace Game {

	using namespace Flare;

	Game_core::Game_core(int window_width, int window_height) :Flare_core{ window_width ,window_height } {}

	void Game_core::initialize() noexcept
	{
		try
		{
			shared_ptr<Sprite> sky{ make_shared<Sprite>("texture/Sky.png") };

			sky->width = 1600;
			sky->height = 900;
			this->get_stage().add_child(sky);

			shared_ptr<Sprite> ground{ make_shared<Sprite>("texture/Ground.png") };
			ground->width = 2000;
			ground->height = 200;
			ground->y = 450;
			this->get_stage().add_child(ground);
		}
		catch (...)
		{
			printf("unable to initialize game core");
		}

	}

	void Game_core::enter_frame() noexcept
	{

	}
}