#include "Flare_core.h"
#include "debug.h"

#include <iostream>
#include <string>

namespace Flare
{
	using namespace std;

	Flare_core::Flare_core(int window_width, int window_height) : renderer{ window_width ,window_height }, window_width{ window_width }, window_height{ window_height }
	{
		dout << "Debug Mode" << endl;

		this->window.initialize("Flare", window_width, window_height);
		this->audio.initialize();
		this->renderer.initialize();
	}

	void Flare_core::initialize() noexcept {}
	void Flare_core::enter_frame() noexcept {}

	void Flare_core::run()
	{
		//Musice music = this->audio.load_music("music/x.ogg");
		//music.play(-1);

		this->initialize();

		string delimiter{ " " };

		while (this->key.currentState != Key::GameState::ended)
		{
			this->enter_frame();
			this->frame_manager.calculate_fps();
			this->key.process();
			this->program.run(this->key, this->renderer, this->audio);
			this->game.run();
			this->renderer.stage.enter_frame();
			this->renderer.text = "fps:" + delimiter + to_string(static_cast <int>(this->frame_manager.frames_per_second) + 1) + "\n" + "object:" + delimiter + to_string(this->renderer.stage.get_size());
			this->renderer.render();
			this->window.swap_window();
		}

		//music.stop();
	}

	Container& Flare_core::get_stage() noexcept
	{
		return this->renderer.stage;
	}
}
