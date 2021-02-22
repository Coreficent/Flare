#include "IOManager.h"
#include <fstream>
#include "error.h"

namespace Dove
{
	using namespace std;

	bool IOManager::readFileToBuffer(string filePath, vector<unsigned char>& buffer)
	{
		ifstream file(filePath, ios::binary);
		if (file.fail())
		{
			fatalError("failed to load binary");
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
