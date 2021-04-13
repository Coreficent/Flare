#pragma once

#include "GL_texture.h"

#include <string>

namespace Flare
{
	using namespace std;

	class ImageLoader
	{
	public:
		static GL_texture loadPNG(string filePath);
	};
}
