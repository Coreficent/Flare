#pragma once

#include "TextureCache.h"

namespace Flare::Texture
{
	class ResourceManager
	{

	public:
		static GLTexture getTexture(std::string filePath);

	private:
		static TextureCache textureCache;
	};

}
