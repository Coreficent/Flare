#pragma once

#include <map>
#include <sdl/SDL_mixer.h>
#include <string>

namespace Flare
{
	using namespace std;

	class Sound
	{
	public:
		Sound(string url);

		void play() noexcept;
		void play(int loop) noexcept;

	private:
		Mix_Chunk* chunk{nullptr};
	};
}
