#include "ImageLoader.h"
#include "Texture_cache.h"

namespace Flare::Texture
{
	using namespace std;

	GLTexture Texture_cache::getTexture(string& filePath)
	{
		auto it = this->textureMap.find(filePath);
		if (it == this->textureMap.end())
		{
			auto texture = ImageLoader::loadPNG(filePath);
			this->textureMap.insert({filePath,texture});
			return texture;
		}
		return it->second;
	}
}
