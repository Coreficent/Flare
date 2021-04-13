#pragma once

#include "Gl_texture.h"

#include <map>
#include <sdl/SDL_mixer.h>
#include <string>

namespace Flare
{
	using namespace std;

	class Resource_manager
	{

	public:
		static GL_texture get_texture(string file_path);
		static Mix_Chunk* get_audio(const string& file_path);

	private:
		inline static map<string, GL_texture> texture_cache{};
		inline static map<string, Mix_Chunk*> audio_cache{};
	};

}
