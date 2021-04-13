#include "IO_manager.h"
#include "error.h"

#include <fstream>

namespace Flare
{
	using namespace std;

	bool IO_manager::read_file_to_buffer(string file_path, vector<unsigned char>& buffer)
	{
		ifstream file(file_path, ios::binary);

		if (file.fail())
		{
			output_error("failed to load binary at " + file_path);
			return false;
		}

		file.seekg(0, ios::end);
		auto fileSize = file.tellg();
		file.seekg(0, ios::beg);

		fileSize -= file.tellg();

		buffer.resize(fileSize);

		file.read(reinterpret_cast<char*>(&buffer[0]), fileSize);
		file.close();

		return true;
	}
}
