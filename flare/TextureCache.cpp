#include "TextureCache.h"
#include "ImageLoader.h"

namespace Flare::Texture
{
	using namespace std;

	GLTexture TextureCache::getTexture(string& filePath)
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
