#pragma once

#include "flare/Key.h"
#include "flare/Sprite.h"

namespace Game
{
	using namespace Flare;

	class Gun : public Sprite
	{

	public:
		Gun(string texture_url);

		void enter_frame() noexcept override;
	};
}
