#include "IOManager.h"
#include "Image_loader.h"
#include "error.h"
#include "picoPNG.h"

namespace Flare
{
	using namespace std;

	GL_texture Image_loader::load_png(const string& filePath)
	{
		GL_texture texture = {};
		vector<unsigned char> input{};
		vector<unsigned char> output{};
		unsigned long width{};
		unsigned long height{};

		if (!IOManager::read_file_to_buffer(filePath, input))
		{
			output_error("failed to load to buffer");
		}

		const auto error_code = decodePNG(output, width, height, &(input.at(0)), input.size(), true);

		if (error_code != 0)
		{
			output_error("decode failed");
		}

		glGenTextures(1, &texture.id);

		glBindTexture(GL_TEXTURE_2D, texture.id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(output.at(0)));

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
