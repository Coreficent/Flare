#include "Resource_manager.h"

namespace Flare::Texture
{
	using namespace std;

	Texture_cache Resource_manager::textureCache;

	GLTexture Resource_manager::getTexture(string filePath)
	{
		return textureCache.getTexture(filePath);
	}
}
