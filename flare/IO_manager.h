#pragma once

#include <string>
#include <vector>

namespace Flare
{
	using namespace std;

	class IO_manager
	{
	public:
		static bool read_file_to_buffer(string filePath, vector<unsigned char>& buffer);
	};
}
