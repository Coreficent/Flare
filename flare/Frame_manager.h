#pragma once

#include <sdl/SDL_stdinc.h>
#include <array>
#include <chrono>
#include <thread>

namespace Flare::Frame
{
	using namespace std::chrono;

	class Frame_manager
	{

	public:
		void calculate_fps();

		float frames_per_second{};

	private:
		std::array<Uint32, 60> samples{};

		Uint32 current_ticks{ 0 };
		Uint32 current_frame{ 0 };
		Uint32 previous_ticks{ 0 };

		system_clock::time_point a = system_clock::now();
		system_clock::time_point b = system_clock::now();

		unsigned int budget{ 16 };
	};
}
