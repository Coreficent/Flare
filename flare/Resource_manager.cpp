#include "ImageLoader.h"
#include "Resource_manager.h"

namespace Flare
{
	using namespace std;

	GLTexture Resource_manager::get_texture(string file_path)
	{
		auto it = Resource_manager::texture_cache.find(file_path);
		if (it == Resource_manager::texture_cache.end())
		{
			auto texture = ImageLoader::loadPNG(file_path);
			Resource_manager::texture_cache.insert({ file_path,texture });
			return texture;
		}
		return it->second;
	}

	Mix_Chunk* Resource_manager::get_audio(const std::string& file_path)
	{
		auto it = Resource_manager::audio_cache.find(file_path);

		if (it == Resource_manager::audio_cache.end())
		{
			Mix_Chunk* chunk = Mix_LoadWAV(file_path.c_str());

			if (chunk == nullptr)
			{
				printf("load sound filed");
				return nullptr;
			}

			Resource_manager::audio_cache[file_path] = chunk;
			return chunk;
		}
		else
		{
			return it->second;
		}
	}
}
