#include <iostream>

#include "Evader_core.h"

namespace Evader {

	using namespace Flare;

	Evader_core::Evader_core(int window_width, int window_height) :Flare_core{ window_width ,window_height } {}

	void Evader_core::initialize() noexcept
	{
		std::cout << "evader core initialized" << std::endl;
	}

	void Evader_core::enter_frame() noexcept
	{
		// std::cout << "evader core enter" << std::endl;
	}
}