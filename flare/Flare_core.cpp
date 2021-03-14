#include "Flare_core.h"
#include "debug.h"
#include <iostream>
#include <string>

namespace Flare::Core
{
	using namespace std;

	Flare_core::Flare_core(int windowWidth, int windowHeight)
		: renderer{ windowWidth ,windowHeight }
	{
		dout << "Debug Mode" << endl;

		this->window.initialize("Flare", windowWidth, windowHeight);
		this->audio.initialize();
		this->renderer.initialize();
	}

	void Flare_core::run()
	{
		Musice music = this->audio.load_music("music/x.ogg");
		music.play(-1);

		while (this->key.currentState != Key::GameState::ended)
		{
			this->enter_frame();
			this->frame_manager.calculate_fps();
			this->key.process();
			this->program.run(this->key, this->renderer, this->audio);
			this->game.run();
			this->renderer.renderNow();
			this->window.swap_window();
		}

		music.stop();
	}

	void Flare_core::enter_frame() noexcept
	{
	}

	Container& Flare_core::get_stage() noexcept
	{
		return this->renderer.stage;
	}
}
