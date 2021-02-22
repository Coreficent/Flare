#pragma once
#include "GlTexture.h"
#include <map>

namespace Dove
{
	class TextureCache
	{
	public:
		TextureCache();
		~TextureCache();

		GLTexture getTexture(std::string& filePath);

	private:
		std::map<std::string, GLTexture> textureMap;
	};
}
