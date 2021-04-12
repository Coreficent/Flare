#include "Resource_manager.h"

namespace Flare
{
	using namespace std;

	GLTexture Resource_manager::get_texture(string file_path)
	{
		return texture_cache.get_texture(file_path);
	}

	Mix_Chunk* Resource_manager::get_audio(const std::string& file_path)
	{
		auto it = Resource_manager::effect_map.find(file_path);

		if (it == Resource_manager::effect_map.end())
		{
			Mix_Chunk* chunk = Mix_LoadWAV(file_path.c_str());

			if (chunk == nullptr)
			{
				printf("load sound filed");
				return nullptr;
			}

			Resource_manager::effect_map[file_path] = chunk;
			return chunk;
		}
		else
		{
			return it->second;
		}
	}
}
