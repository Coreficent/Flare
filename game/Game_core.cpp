#include "Game_core.h"

#include <iostream>

namespace Game {

	using namespace Flare;

	Game_core::Game_core(int window_width, int window_height) :Flare_core{ window_width ,window_height } {}

	void Game_core::initialize() noexcept
	{
		shared_ptr<Sprite> sky{ new Sprite{"texture/Sky.png" } };
		sky->width = 1600;
		sky->height = 900;

		this->get_stage().add_child(sky);
	}

	void Game_core::enter_frame() noexcept
	{

	}
}