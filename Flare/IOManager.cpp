#include "IOManager.h"
#include <fstream>
#include "error.h"

using namespace std;

bool IOManager::readFileToBuffer(string filePath, vector<char>& buffer)
{
	ifstream file(filePath, ios::binary);
	if(file.fail())
	{
		fatalError("failed to load binary");
		return false;
	}

	file.seekg(0, ios::end);
	int fileSize = file.tellg();
	file.seekg(0, ios::beg);

	fileSize -= file.tellg();

	buffer.resize(fileSize);
	file.read(&buffer[0], fileSize);
	file.close();

	return true;
}
