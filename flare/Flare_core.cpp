#include "Flare_core.h"
#include "debug.h"

#include <iostream>
#include <string>

namespace Flare
{
	using namespace std;

	Flare_core::Flare_core(int window_width, int window_height) : window_width{ window_width }, window_height{ window_height }
	{
		dout << "Debug Mode" << endl;
	}

	void Flare_core::initialize() noexcept {}

	void Flare_core::running()
	{
		//Musice music = this->audio.load_music("music/x.ogg");
		//music.play(-1);

		this->audio.initialize();
		this->renderer.initialize();
		this->initialize();

		while (Key::state != Key::Game_state::ending)
		{
			this->enter_frame();
			this->frame_manager.calculate_fps();
			Key::process();
			this->program.running(this->renderer, this->audio);
			this->renderer.render(*this);
			this->window.swap_window();
		}

		//music.stop();
	}
}
