#include "Bunny.h"

namespace Benchmark
{
	void Bunny::enter_frame() noexcept
	{
		this->x += this->speed_x;
		this->y += this->speed_y;
		this->speed_y += gravity;

		if (this->x > this->maximum_x)
		{
			this->speed_x *= -1;
			this->x = this->maximum_x;
		}
		else if (this->x < this->minimum_x)
		{
			this->speed_x *= -1;
			this->x = this->minimum_x;
		}
		if (this->y > this->maximum_y)
		{
			this->speed_y *= -0.8f;
			this->y = this->maximum_y;
			if (rand() % 10 > 5)
			{
				this->speed_y -= 3 + rand() % 10 / 10.0f * 4.0f;
			}
		}
		else if (this->y < this->minimum_y)
		{

			this->speed_y = 0;
			this->y = this->minimum_y;
		}
	}
}
