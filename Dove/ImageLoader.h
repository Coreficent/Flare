#pragma once
#include "GLTexture.h"
#include <string>

namespace Dove
{
	class ImageLoader
	{
	public:
		static GLTexture loadPNG(std::string filePath);
	};
}
