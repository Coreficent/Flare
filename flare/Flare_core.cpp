#include "Flare_core.h"
#include "debug.h"

#include <iostream>
#include <string>

namespace Flare
{
	using namespace std;

	Flare_core::Flare_core(int window_width, int window_height) : window_width{ window_width }, window_height{ window_height }, stage{ *this }
	{
		dout << "Debug Mode" << endl;
	}

	void Flare_core::initialize() noexcept {}

	void Flare_core::run()
	{
		//Musice music = this->audio.load_music("music/x.ogg");
		//music.play(-1);

		this->audio.initialize();
		this->renderer.initialize();
		this->initialize();

		while (this->key.currentState != Key::GameState::ended)
		{
			this->stage.enter_frame();
			this->frame_manager.calculate_fps();
			this->key.process();
			this->program.run(this->key, this->renderer, this->audio);
			this->renderer.render(this->stage);
			this->window.swap_window();
		}

		//music.stop();
	}
}
