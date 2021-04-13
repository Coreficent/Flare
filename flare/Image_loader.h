#pragma once

#include "GL_texture.h"

#include <string>

namespace Flare
{
	using namespace std;

	class Image_loader
	{
	public:
		static GL_texture load_png(const string& file_path);
	};
}
