#pragma once

#include <sdl/SDL_stdinc.h>
#include <array>

namespace Flare::Frame
{
	class FrameManager
	{

	public:
		void calculate_fps();

	private:
		std::array<Uint32, 60> samples{};

		Uint32 current_ticks{ 0 };
		Uint32 current_frame{ 0 };
		Uint32 previous_ticks{ 0 };

		unsigned int budget{ 16 };
	};
}
