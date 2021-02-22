#pragma once
#include "TextureCache.h"

namespace Dove
{
	class ResourceManager
	{
	public:
		static GLTexture getTexture(std::string filePath);

	private:
		static TextureCache textureCache;
	};
}
