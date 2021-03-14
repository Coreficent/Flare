#include "Frame_manager.h"
#include <array>
#include <sdl/SDL_stdinc.h>
#include <sdl/SDL.h>
#include "debug.h"

namespace Flare::Frame
{
	using namespace std;

	void Frame_manager::calculate_fps()
	{
		this->a = std::chrono::system_clock::now();
		std::chrono::duration<double, std::milli> work_time = this->a - this->b;

		double second{ 1000.0 };
		double budget{ second / 60.0 };


		if (work_time.count() < budget)
		{
			std::chrono::duration<double, std::milli> delta_ms(budget - work_time.count());
			auto delta_ms_duration = std::chrono::duration_cast<std::chrono::milliseconds>(delta_ms);
			std::this_thread::sleep_for(std::chrono::milliseconds(delta_ms_duration.count()));
		}

		this->b = std::chrono::system_clock::now();
		std::chrono::duration<double, std::milli> sleep_time = this->b - this->a;

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
