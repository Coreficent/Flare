#pragma once

#include <sdl/SDL_stdinc.h>
#include <array>
#include <chrono>
#include <thread>

namespace Flare::Frame
{
	using namespace std;
	using namespace std::chrono;

	class Frame_manager
	{

	public:
		void calculate_fps();

		double frames_per_second{ 0.0 };
		double remaining_budget{ 0.0 };

	private:
		array<Uint32, 60> samples{};

		system_clock::time_point time_before_sleep = system_clock::now();
		system_clock::time_point time_after_sleep = system_clock::now();
	};
}
