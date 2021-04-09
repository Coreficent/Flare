#include "Frame_manager.h"
#include <array>
#include <sdl/SDL_stdinc.h>
#include <sdl/SDL.h>
#include "debug.h"

namespace Flare
{
	using namespace std;
	using namespace std::chrono;

	Frame_manager::Frame_manager() {
		for (auto i{ 0 }; i < 100; ++i) {
			this->frame_rates.push(0.0);
		}
	}

	void Frame_manager::calculate_fps()
	{
		this->time_before_sleep = system_clock::now();
		const duration<double, std::milli> run_time = this->time_before_sleep - this->time_after_sleep;

		constexpr double second{ 1000.0 };
		constexpr double budget{ second / 60.0 };

		this->remaining_budget = budget - run_time.count();

		if (this->remaining_budget > 0.0)
		{
			const duration<double, milli> delta_ms(budget - run_time.count());
			auto delta_ms_duration = duration_cast<milliseconds>(delta_ms);
			this_thread::sleep_for(milliseconds(delta_ms_duration.count()));
		}

		this->time_after_sleep = system_clock::now();

		const duration<double, std::milli> sleep_time = this->time_after_sleep - this->time_before_sleep;
		const double current_frame_rate = second / (run_time + sleep_time).count();

		this->frame_rates.push(current_frame_rate);
		this->frame_rates.pop();

		double total_frame_rate{};

		queue <double> rates = this->frame_rates;

		while (!rates.empty())
		{
			total_frame_rate += rates.front();
			rates.pop();
		}

		this->frames_per_second = total_frame_rate / this->frame_rates.size();
	}
}
