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
	}

	void Flare_core::initialize() noexcept {}
	void Flare_core::enter_frame() noexcept {}

	void Flare_core::run()
	{
		//Musice music = this->audio.load_music("music/x.ogg");
		//music.play(-1);
		this->audio.initialize();

		this->renderer.initialize();
		this->initialize();

		while (this->key.currentState != Key::GameState::ended)
		{
			this->enter_frame();
			this->frame_manager.calculate_fps();
			this->key.process();
			this->program.run(this->key, this->renderer, this->audio);
			this->game.run();
			this->renderer.stage.enter_frame();
			this->renderer.render();
			this->window.swap_window();
		}

		//music.stop();
	}

	Sprite& Flare_core::get_stage() noexcept
	{
		return this->renderer.stage;
	}
}
