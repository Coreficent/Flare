#include "Benchmark_core.h"
#include <iostream>

namespace Benchmark::Core {
	using namespace Benchmark::Core;


	Benchmark_core::Benchmark_core(int window_width, int window_height) :Flare_core{ window_width ,window_height }
	{

	}

	void Benchmark_core::enter_frame() noexcept
	{
		std::cout << "entering frame from benchmark" << std::endl;
		this->get_stage();
	}
}
