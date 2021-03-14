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
		GLTexture get_texture(string& file_path);

	private:
		map<string, GLTexture> texture_map;
	};

}
