#include "mathematics.h"

namespace Dove
{
	float to_radian(float value)
	{
		return value * PI / 180;
	}

	float to_degree(float value)
	{
		return value * 180 / PI;
	}
}
