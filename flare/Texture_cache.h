#pragma once

#include "GlTexture.h"
#include <map>
#include <string>

namespace Flare::Texture
{
	using namespace std;

	class Texture_cache
	{

	public:
		GLTexture getTexture(string& filePath);

	private:
		map<string, GLTexture> textureMap;
	};

}
