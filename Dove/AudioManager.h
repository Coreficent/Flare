#pragma once
#include <string>
#include <sdl/SDL_stdinc.h>

namespace Dove
{
	struct Audio
	{
		Uint8* position;
		Uint32 length;
	};


	class AudioManager
	{
	public:
		AudioManager();
		~AudioManager();
		void load(const std::string& file_path);
		static void audio_callback(void* user_data, Uint8* stream, int stream_length);
	};
}
