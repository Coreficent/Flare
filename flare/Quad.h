#pragma once

#include <gl/glew.h>
#include "GlTexture.h"
#include <string>


namespace Flare
{
	class Quad
	{
	public:
		Quad(float x, float y, float width, float height);
		~Quad();

		void initialize(std::string texturePath);
		void draw();

	private:
		GLTexture quadTexture;

		GLuint vertextBufferID;

		float x, y, width, height;
	};
}
