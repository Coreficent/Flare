#include "ResourceManager.h"
using namespace std;

namespace Flare::Texture
{
	Texture_cache Resource_manager::textureCache;

	GLTexture Resource_manager::getTexture(string filePath)
	{
		return textureCache.getTexture(filePath);
	}
}
