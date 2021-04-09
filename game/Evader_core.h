#pragma once

#include "flare/Flare_core.h"

namespace Evader {

	using namespace Flare;

	class Evader_core : public Flare_core
	{

	public:
		Evader_core(int windowWidth, int windowHeight);

		void initialize() noexcept override;
		void enter_frame() noexcept override;

	private:
	};
}
