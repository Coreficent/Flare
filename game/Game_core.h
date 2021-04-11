#pragma once

#include "flare/Flare_core.h"

namespace Game {

	using namespace Flare;

	class Game_core : public Flare_core
	{

	public:
		Game_core(int windowWidth, int windowHeight);

		void initialize() noexcept override;
		void enter_frame() noexcept override;

	private:

	};
}
