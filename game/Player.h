#pragma once

#include "flare/Key.h"
#include "flare/Sprite.h"

namespace Game
{
	using namespace Flare;

	class Player : public Sprite
	{

	public:
		Player(string texture_url, Key& key);

		void enter_frame() noexcept override;

	private:
		Key& key;
	};
}
