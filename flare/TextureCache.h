#pragma once

#include "GlTexture.h"
#include <map>
#include <string>

namespace Flare::Texture
{
	class TextureCache
	{

	public:
		GLTexture getTexture(std::string& filePath);

	private:
		std::map<std::string, GLTexture> textureMap;
	};

}
