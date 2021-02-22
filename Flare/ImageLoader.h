#pragma once
#include "glTexture.h"
#include <string>

using namespace std;

class ImageLoader
{
public:
	static GLTexture loadPNG(string filePath);
};

