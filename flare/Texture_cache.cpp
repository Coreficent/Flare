#include "ImageLoader.h"
#include "Texture_cache.h"

namespace Flare
{
	using namespace std;

	GLTexture Texture_cache::get_texture(string& file_path)
	{
		auto it = this->texture_map.find(file_path);
		if (it == this->texture_map.end())
		{
			auto texture = ImageLoader::loadPNG(file_path);
			this->texture_map.insert({ file_path,texture });
			return texture;
		}
		return it->second;
	}
}
