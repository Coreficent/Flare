#include "ImageLoader.h"
#include "picoPNG.h"
#include "IOManager.h"
#include "error.h"

namespace Dove
{
	using namespace std;

	GLTexture ImageLoader::loadPNG(string filePath)
	{
		GLTexture texture = {};
		vector<unsigned char> input{};
		vector<unsigned char> output{};
		unsigned long width;
		unsigned long height;

		if (!IOManager::readFileToBuffer(filePath, input))
		{
			fatalError("failed to load to buffer");
		}

		auto errorCode = decodePNG(output, width, height, &(input[0]), input.size(), true);
		if (errorCode != 0)
		{
			fatalError("decode failed");
		}

		glGenTextures(1, &texture.id);

		glBindTexture(GL_TEXTURE_2D, texture.id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(output[0]));

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);

		texture.width = width;
		texture.height = height;

		return texture;
	}
}
