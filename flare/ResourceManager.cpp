#include "ResourceManager.h"
using namespace std;

namespace Flare::Texture
{
	Texture_cache ResourceManager::textureCache;

	GLTexture ResourceManager::getTexture(string filePath)
	{
		return textureCache.getTexture(filePath);
	}
}
