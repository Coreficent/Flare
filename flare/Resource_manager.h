#pragma once

#include "Texture_cache.h"

namespace Flare
{
	class Resource_manager
	{

	public:
		static GLTexture get_texture(std::string file_path);

	private:
		static Texture_cache texture_cache;
	};

}
