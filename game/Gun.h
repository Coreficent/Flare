#pragma once

#include "flare/Sprite.h"

namespace Game
{
	using namespace Flare;

	class Gun : public Sprite
	{

	public:
		Gun(string texture_url, shared_ptr<Sprite> spawn_layer);
		void enter_frame() noexcept override;

		shared_ptr<Sprite> spawn_layer{};
	};
}