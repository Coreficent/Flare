#pragma once

#include <flare/Sprite.h>

namespace Game
{
	using namespace Flare;

	class Debris : public Sprite
	{

	public:
		Debris(string texture_url, float mass);

		void enter_frame() noexcept override;
		float mass{ 10.0f };
		float speed{ 10.0f };

	private:
	};
}