#include "ResourceManager.h"

TextureCache ResourceManager::textureCache;

GLTexture ResourceManager::getTexture(string filePath)
{
	return textureCache.getTexture(filePath);
}
