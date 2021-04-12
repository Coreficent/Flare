#pragma once

#include <flare/Sprite.h>

namespace Game
{
	using namespace Flare;

	class Spawner : public Sprite
	{

	public:
		Spawner() noexcept;
		Spawner(shared_ptr<Sprite> spawn_layer) noexcept;

		void enter_frame() override;

		shared_ptr<Sprite> spawn_layer{};

	protected:
		unsigned int frame{0};
	};
}