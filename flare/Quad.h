#pragma once

#include "Vertex.h"

#include <glm/glm.hpp>

namespace Flare
{
	using namespace glm;

	struct Quad
	{
		unsigned int texture_id;

		Position top_left;
		Position top_right;
		Position bottom_left;
		Position bottom_right;

		vec4 uv;
	};
}
