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

		float frames_per_second{};

	private:
		array<Uint32, 60> samples{};

		system_clock::time_point a = system_clock::now();
		system_clock::time_point b = system_clock::now();
	};
}
