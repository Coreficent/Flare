#include "FrameManager.h"
#include <array>
#include <sdl/SDL_stdinc.h>
#include <sdl/SDL.h>
#include "debug.h"

namespace Flare
{
	using namespace std;

	FrameManager::FrameManager()
	{
	}


	FrameManager::~FrameManager()
	{
	}

	void FrameManager::calculate_fps()
	{
		this->current_ticks = SDL_GetTicks();
		auto current_cost = this->current_ticks - this->previous_ticks;
		this->previous_ticks = this->current_ticks;

		this->samples[this->current_frame++ % this->samples.size()] = current_cost;

		Uint32 average_cost{0};
		for (auto& i : this->samples)
		{
			average_cost += i;
		}
		auto fps = 1000.0f / ((average_cost + 0.0001f) / this->samples.size());
		auto remaining_budget = static_cast<int>(this->budget - current_cost);

		if (this->budget > current_cost)
		{
			SDL_Delay(remaining_budget);
		}

		if (!(this->current_frame % 60))
		{
			cout << "fps: " << fps << " budget " << remaining_budget << endl;
		}
	}
}