#pragma once

#include <string>
#include <vector>

namespace Flare
{
	class IOManager
	{
	public:
		static bool read_file_to_buffer(std::string filePath, std::vector<unsigned char>& buffer);
	};
}
