#pragma once

#include "Texture_cache.h"
#include <sdl/SDL_mixer.h>

namespace Flare
{
	class Resource_manager
	{

	public:
		static GLTexture get_texture(std::string file_path);
		static Mix_Chunk* Resource_manager::get_audio(const std::string& file_path);

	private:
		inline static Texture_cache texture_cache{};
		inline static map<string, Mix_Chunk*> effect_map{};
	};

}
