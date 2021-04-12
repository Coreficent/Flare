#pragma once

#include <flare/Sprite.h>

namespace Game
{
	using namespace Flare;

	class Bullet : public Sprite
	{

	public:
		Bullet(string texture_url, int window_height);

		void enter_frame() noexcept override;

		float speed_x{ 0.0f };
		float speed_y{ 0.0f };

		float damage{ 1.0f };

	private:
		int window_height;
	};
}