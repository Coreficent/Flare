#pragma once

#include "GlTexture.h"

#include <map>
#include <sdl/SDL_mixer.h>
#include <string>

namespace Flare
{
	using namespace std;

	class Resource_manager
	{

	public:
		static GLTexture get_texture(string file_path);
		static Mix_Chunk* Resource_manager::get_audio(const string& file_path);

	private:
		inline static map<string, GLTexture> texture_map{};
		inline static map<string, Mix_Chunk*> effect_map{};
	};

}
