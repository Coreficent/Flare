#include <iostream>
#include <string>
#include "Core.h"
#include "debug.h"

namespace Dove
{
	using namespace std;

	Core* Core::core{nullptr};

	Core::Core(int windowWidth, int windowHeight)
		: renderer{windowWidth ,windowHeight}
	{
		dout << "Debug Mode" << endl;

		this->window.initialize("Dove", windowWidth, windowHeight);

		this->audio.initialize();


		this->renderer.initialize();


		core = this;
	}

	Core::~Core()
	{
	}

	void Core::run()
	{
		Musice music = this->audio.load_music("music/x.ogg");
		music.play(-1);

		while (this->key.currentState != Key::GameState::ended)
		{
			this->frame_manager.calculate_fps();

			this->key.process();


			this->program.run(this->key, this->renderer, this->audio);


			this->game.run();

			this->renderer.renderNow();

			this->window.swap_window();
		}
		music.stop();
	}
}
