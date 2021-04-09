#pragma once

#include "flare/Flare_core.h"

namespace Evader {

	using namespace Flare::Core;

	class Evader_core : public Flare_core
	{

	public:
		Evader_core(int windowWidth, int windowHeight);

		void enter_frame() noexcept override;

	private:
		void adjust_bunny() noexcept;

	};
}
