#include "Bunny.h"
#include <iostream>

namespace Benchmark::Display
{
	void Bunny::enter_frame() noexcept {
		this->set_x(this->get_x() + 1.0f);
		std::cout << "bunny enter frame" << std::endl;
	}
}
