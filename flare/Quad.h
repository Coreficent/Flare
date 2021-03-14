#pragma once

#include <glm/glm.hpp>

namespace Flare::Display
{
	using namespace glm;

	struct Quad
	{
		unsigned int texture_id;
		vec4 bound;
		vec4 uv;
	};
}