#pragma once

#include "flare/Flare_core.h"

namespace Benchmark::Core {

	using namespace Flare;

	class Benchmark_core : public Flare_core
	{

	public:
		Benchmark_core(int windowWidth, int windowHeight);

		void enter_frame() noexcept override;

	private:
		void adjust_bunny() noexcept;

	};
}
