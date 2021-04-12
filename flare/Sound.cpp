#include "Sound.h"
#include "Resource_manager.h"

#include <sdl/SDL_mixer.h>


namespace Flare
{
	Sound::Sound(string url)
	{
		Mix_Chunk* chunk = Resource_manager::get_audio(url);
		if (chunk)
		{
			this->chunk = chunk;
		}
		else
		{
			printf("unable to create audio\n");
		}
	}

	void Sound::play() noexcept
	{
		Sound::play(0);
	}

	void Sound::play(int loop) noexcept
	{
		if (Mix_PlayChannel(-1, this->chunk, loop) == -1)
		{
			if (Mix_PlayChannel(rand() % 8, this->chunk, loop) == -1)
			{
				printf("no channel left");
			}
		}
	}
}
