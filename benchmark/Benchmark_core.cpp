#include "Benchmark_core.h"
#include <flare/Sprite.h>
#include <flare/Resource_manager.h>
#include <iostream>

namespace Benchmark::Core {

	using namespace Benchmark::Core;
	using namespace Flare::Display;

	Benchmark_core::Benchmark_core(int window_width, int window_height) :Flare_core{ window_width ,window_height }
	{

	}

	void Benchmark_core::enter_frame() noexcept
	{
		this->add_bunny();
		this->animate();
	}

	void Benchmark_core::add_bunny() noexcept
	{
		static auto bunny_texture = Flare::Texture::Resource_manager::get_texture("texture/cake.png");
		static auto x{ 0.0f };

		if (this->frame_manager.frames_per_second > 60.0f) {
			Sprite bunny{};

			bunny.set_texture_id(bunny_texture.id);

			bunny.set_width(100.0f);
			bunny.set_height(100.0f);

			bunny.set_x(x++);

			this->get_stage().add_child(bunny);
		}
	}

	void Benchmark_core::animate() noexcept
	{
		for (auto& child : this->get_stage().children) {
			child.set_y(child.get_y() + 1.0f);
		}
	}

}
