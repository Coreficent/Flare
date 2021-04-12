#include "Flare_core.h"
#include "debug.h"
#include "Sound.h"

#include <iostream>
#include <string>

namespace Flare
{
	using namespace std;

	Flare_core::Flare_core(int window_width, int window_height) : window_width{ window_width }, window_height{ window_height }
	{
		dout << "Debug Mode" << endl;
	}

	void Flare_core::initialize() {}

	void Flare_core::run()
	{
		//Musice music = this->audio.load_music("music/x.ogg");
		//music.play(-1);

		this->audio.initialize();
		this->renderer.initialize();
		this->initialize();

		Sound test{ "sound/bounce.wav" };

		while (!Key::is_down(SDLK_ESCAPE) && !Key::is_down(SDL_QUIT))
		{
			this->enter_frame();
			this->frame_manager.calculate_fps();
			Key::process();
			//this->program.run(this->renderer, this->audio);
			this->renderer.render(*this);
			this->window.update_window();

			test.play();
		}

		//music.stop();
	}
}
