#include "Resource_manager.h"

namespace Flare
{
	using namespace std;

	Texture_cache Resource_manager::texture_cache;

	GLTexture Resource_manager::get_texture(string file_path)
	{
		return texture_cache.get_texture(file_path);
	}
}
