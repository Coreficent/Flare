#pragma once

#include "flare/Sprite.h"

namespace Game
{
	using namespace Flare;

	class Debris : public Sprite
	{

	public:
		Debris(string texture_url);

		void enter_frame() noexcept override;

	private:
		float speed{ 1.0f };
	};
}