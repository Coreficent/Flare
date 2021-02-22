#include "FrameManager.h"
#include <array>
#include <sdl/SDL_stdinc.h>
#include <sdl/SDL.h>
#include "error.h"

namespace Dove {

	FrameManager::FrameManager() :currentTicks{ 0 }, budget{ 16 }
	{
	}


	FrameManager::~FrameManager()
	{
	}

	void FrameManager::calculateFPS()
	{
		static const auto SAMPLE_SIZE{ 50 };
		static std::array<Uint32, SAMPLE_SIZE> frameTimes{ 0,0,0 };
		static auto currentFrame{ 0 };
		static auto previousTicks = SDL_GetTicks();

		this->currentTicks = SDL_GetTicks();
		auto frameTime = this->currentTicks - previousTicks;
		previousTicks = this->currentTicks;

		frameTimes[currentFrame++ % SAMPLE_SIZE] = frameTime;

		auto averageFrameTime{ 0.0f };
		for (auto& i : frameTimes)
		{
			averageFrameTime += i;
		}
		averageFrameTime = averageFrameTime / SAMPLE_SIZE + 0.0001f;
		auto fps = 1000.0f / averageFrameTime;

		if (!(currentFrame % 60))
		{
			Dove::debugPrint("fps: ");
			printf("%f\n", fps);
		}
		auto frameTicks = SDL_GetTicks() - this->currentTicks;
		if (this->budget > frameTicks)
		{
			SDL_Delay(this->budget - frameTicks - 1);
		}
	
	}
}
