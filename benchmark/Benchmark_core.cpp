#include "Benchmark_core.h"
#include "Bunny.h"
#include <flare/Sprite.h>
#include <flare/Resource_manager.h>
#include <iostream>

namespace Benchmark::Core {

	using namespace Benchmark::Core;
	using namespace Benchmark::Display;
	using namespace Flare::Display;

	Benchmark_core::Benchmark_core(int window_width, int window_height) :Flare_core{ window_width ,window_height } {}

	void Benchmark_core::enter_frame() noexcept
	{
		this->adjust_bunny();
	}

	void Benchmark_core::adjust_bunny() noexcept
	{
		static auto bunny_texture = Flare::Texture::Resource_manager::get_texture("texture/cake.png");

		if (this->frame_manager.frames_per_second > 60.0f) {

			for (auto i{ 0 }; i < this->frame_manager.remaining_budget; ++i) {

				shared_ptr<Bunny> bunny{ new Bunny{} };

				bunny->texture_id = bunny_texture.id;
				bunny->width = bunny->height = 100.0f;

				bunny->minimum_x = this->window_width / -2.0f;
				bunny->minimum_y = this->window_height / -2.0f;
				bunny->maximum_x = this->window_width / 2.0f;
				bunny->maximum_y = this->window_height / 2.0f;

				bunny->x = bunny->minimum_x;
				bunny->y = bunny->minimum_y;

				this->get_stage().add_child(bunny);
			}
		}
		else if (this->frame_manager.frames_per_second < 55.0f) {
			this->get_stage().reomve_last_child();
		}
	}
}
