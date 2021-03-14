#pragma once

#include "Texture_cache.h"

namespace Flare::Texture
{
	class ResourceManager
	{

	public:
		static GLTexture getTexture(std::string filePath);

	private:
		static Texture_cache textureCache;
	};

}
