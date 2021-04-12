#pragma once

#include "flare/Sprite.h"

namespace Game
{
	using namespace Flare;

	class Bullet : public Sprite
	{

	public:
		Bullet(string texture_url, int window_height);

		void enter_frame() override;

	private:
		float speed{ 15.0f };
		int window_height;
	};
}