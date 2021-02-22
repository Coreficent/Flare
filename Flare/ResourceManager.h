#pragma once
#include "TextureCache.h"

class ResourceManager
{
public:
	static GLTexture getTexture(string filePath);

private:
	static TextureCache textureCache;
};
