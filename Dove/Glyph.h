#pragma once
#include "Vertex.h"

namespace Flare
{
	class Glyph
	{
	public:
		Glyph();
		~Glyph();

		GLuint texture{0};
		float depth{0.0f};

		Vertex down_left;
		Vertex top_left;
		Vertex top_right;
		Vertex down_right;
	};
}
