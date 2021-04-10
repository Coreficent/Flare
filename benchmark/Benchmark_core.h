#pragma once

#include "Bunny.h"

#include <flare/Flare_core.h>
#include <flare/Sprite.h>

namespace Benchmark {

	using namespace std;
	using namespace Flare;

	class Benchmark_core : public Flare_core
	{

	public:
		Benchmark_core(int windowWidth, int windowHeight);

		void initialize() noexcept override;
		void enter_frame() noexcept override;

	private:
		vector< shared_ptr<Bunny>> bunnies{};

		void adjust_bunny() noexcept;
	};
}
