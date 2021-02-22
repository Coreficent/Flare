#include "ResourceManager.h"
using namespace std;

namespace Flare
{
	TextureCache ResourceManager::textureCache;

	GLTexture ResourceManager::getTexture(string filePath)
	{
		return textureCache.getTexture(filePath);
	}
}
