#include "IOManager.h"
#include "error.h"

#include <fstream>

namespace Flare
{
	using namespace std;

	bool IOManager::read_file_to_buffer(string filePath, vector<unsigned char>& buffer)
	{
		ifstream file(filePath, ios::binary);

		if (file.fail())
		{
			output_error("failed to load binary at " + filePath);
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
