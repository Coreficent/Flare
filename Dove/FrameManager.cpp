#include "FrameManager.h"
#include <array>
#include <sdl/SDL_stdinc.h>
#include <sdl/SDL.h>
#include "error.h"

namespace Dove
{
	FrameManager::FrameManager()
	{
	}


	FrameManager::~FrameManager()
	{
	}

	void FrameManager::calculate_fps()
	{
		this->current_ticks = SDL_GetTicks();
		auto current_cost = this->current_ticks - previous_ticks;
		previous_ticks = this->current_ticks;

		samples[current_frame++ % samples.size()] = current_cost;

		Uint32 average_cost{0};
		for (auto& i : samples)
		{
			average_cost += i;
		}
		auto fps = 1000.0f / ((average_cost + 0.0001f) / samples.size());


		if (this->budget > current_cost)
		{
			SDL_Delay(this->budget - current_cost - 1);
		}

		if (!(current_frame % 60))
		{
			debugPrint("fps: ");
			printf("%f :: budget %d\n", fps, (this->budget - current_cost - 1));
		}
	}
}
