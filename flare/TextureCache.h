#pragma once

#include <map>
#include <string>

#include "GlTexture.h"

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
