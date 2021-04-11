#pragma once

#include <chrono>
#include <queue>
#include <sdl/SDL_stdinc.h>
#include <thread>

namespace Flare
{
	using namespace std;
	using namespace std::chrono;

	class Frame_manager
	{

	public:
		Frame_manager();

		void calculate_fps();

		double frames_per_second{ 0.0 };
		double remaining_budget{ 0.0 };

	private:
		queue <double> frame_rates{};

		system_clock::time_point time_before_sleep = system_clock::now();
		system_clock::time_point time_after_sleep = system_clock::now();
	};
}
