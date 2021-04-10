#include "Benchmark_core.h"

#include <flare/Resource_manager.h>
#include <flare/Sprite.h>
#include <iostream>

namespace Benchmark {

	using namespace Benchmark;
	using namespace Flare;

	Benchmark_core::Benchmark_core(int window_width, int window_height) :Flare_core{ window_width ,window_height } {}

	void Benchmark_core::initialize() noexcept
	{
		this->statistics->text = "statistics";
		this->statistics->x = -400.0f;
		this->statistics->y = -200.0f;
		this->statistics->scale_y = 2.0f;

		this->get_stage().scale_x = 0.5f;
		this->get_stage().scale_y = 0.5f;
		this->get_stage().rotation = 15.0f;

		this->get_stage().add_child(this->bunny_layer);
		this->get_stage().add_child(this->interface_layer);

		this->interface_layer->add_child(this->statistics);
	}

	void Benchmark_core::enter_frame() noexcept
	{
		this->adjust_bunny();
	}

	void Benchmark_core::adjust_bunny() noexcept
	{
		static auto bunny_texture = Flare::Resource_manager::get_texture("texture/wabbit.png");

		if (this->frame_manager.frames_per_second > 59.5)
		{
			for (auto i{ 0 }; i < this->frame_manager.remaining_budget * this->frame_manager.remaining_budget; ++i)
			{

				shared_ptr<Bunny> bunny{ new Bunny{} };

				bunny->texture_id = bunny_texture.id;
				bunny->width = 26.0f;
				bunny->height = 37.0f;

				bunny->rotation = 45.0f;
				bunny->scale_x = 2.0f;
				bunny->scale_y = 4.0f;

				bunny->minimum_x = this->window_width / -2.0f;
				bunny->minimum_y = this->window_height / -2.0f;
				bunny->maximum_x = this->window_width / 2.0f;
				bunny->maximum_y = this->window_height / 2.0f;

				bunny->x = bunny->minimum_x;
				bunny->y = bunny->minimum_y;

				this->bunnies.push_back(bunny);
				this->bunny_layer->add_child(bunny);
			}
		}
		else if (this->frame_manager.frames_per_second < 59.0f)
		{
			if (!this->bunnies.empty())
			{
				auto last_bunny = this->bunnies.back();
				this->bunnies.pop_back();
				this->bunny_layer->remove_child(last_bunny);
			}
		}

		string delimiter{ " " };
		this->statistics->text = "fps:" + delimiter + to_string(static_cast <int>(this->frame_manager.frames_per_second) + 1) + "\n" + "object:" + delimiter + to_string(this->renderer.stage.child_count() + this->bunnies.size());
	}
}
