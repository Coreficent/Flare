#pragma once
#include "GlTexture.h"
#include <map>

using namespace std;

class TextureCache
{
public:
	TextureCache();
	~TextureCache();

	GLTexture getTexture(string filePath);

private:
	map<string, GLTexture> textureMap;

};
