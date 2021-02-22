#pragma once
#include <sdl/SDL_stdinc.h>

namespace Dove
{
	class FrameManager
	{
	public:
		FrameManager();
		~FrameManager();
		void calculateFPS();
	private:
		Uint32 currentTicks;
		unsigned int budget;
	};
}
