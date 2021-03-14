#pragma once

#include "Texture_cache.h"

namespace Flare::Texture
{
	class Resource_manager
	{

	public:
		static GLTexture getTexture(std::string filePath);

	private:
		static Texture_cache textureCache;
	};

}
