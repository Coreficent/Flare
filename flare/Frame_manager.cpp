#include "Frame_manager.h"
#include <array>
#include <sdl/SDL_stdinc.h>
#include <sdl/SDL.h>
#include "debug.h"

namespace Flare::Frame
{
	using namespace std;
	using namespace std::chrono;


	void Frame_manager::calculate_fps()
	{
		this->a = system_clock::now();
		const duration<double, std::milli> work_time = this->a - this->b;

		constexpr double second{ 1000.0 };
		constexpr double budget{ second / 60.0 };


		this->remaining_budget = budget - work_time.count();

		if (this->remaining_budget > 0.0)
		{
			const duration<double, milli> delta_ms(budget - work_time.count());
			auto delta_ms_duration = duration_cast<milliseconds>(delta_ms);
			this_thread::sleep_for(milliseconds(delta_ms_duration.count()));
		}

		this->b = system_clock::now();
		const duration<double, std::milli> sleep_time = this->b - this->a;

		// Your code here

		// printf("Time: %f \n", (work_time + sleep_time).count());

		this->frames_per_second = second / (work_time + sleep_time).count();





		//this->current_ticks = SDL_GetTicks();
		//auto current_cost = this->current_ticks - this->previous_ticks;
		//this->previous_ticks = this->current_ticks;

		//this->samples.at(this->current_frame++ % this->samples.size()) = current_cost;

		//Uint32 average_cost{ 0 };

		//for (auto& i : this->samples)
		//{
		//	average_cost += i;
		//}

		//const auto fps = 1000.0f / ((average_cost + 0.0001f) / this->samples.size());
		//const int remaining_budget = this->budget - current_cost;

		//if (this->budget > current_cost)
		//{
		//	SDL_Delay(remaining_budget);
		//}

		//if (!(this->current_frame % 60))
		//{
		//	cout << "fps: " << fps << " budget " << remaining_budget << endl;
		//}

		//this->frames_per_second = fps;
	}
}
