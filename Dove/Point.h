#pragma once
namespace Flare
{
	class Point
	{
	public:
		Point();
		Point(float x, float y);
		~Point();

		float x{0.0f};
		float y{0.0f};
	};
}
