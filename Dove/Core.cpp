#include <iostream>
#include <string>
#include "Core.h"
#include "ResourceManager.h"
#include "Display.h"
#include "mathematics.h"
#include "debug.h"

namespace Dove
{
	using namespace std;

	Core* Core::core{nullptr};

	Core::Core(int windowWdith, int windowHeight)
		: quad_batch_{windowWdith ,windowHeight}, input_manager{}, frame_manager{}, currentState{GameState::running}, currentTicks{0}, windowWidth{windowWdith}, windowHeight{windowHeight}
	{
		dout << "<Debug Mode>" << endl;

		this->window.initialize("Dove", this->windowWidth, this->windowHeight);

		this->audio.initialize();


		this->quad_batch_.initialize();


		core = this;
	}

	Core::~Core()
	{
	}

	void Core::run()
	{
		Musice music = this->audio.load_music("music/x.ogg");
		music.play(-1);

		// running the game logic
		this->gameLoop();
	}


	// main loop
	void Core::gameLoop()
	{
		while (this->currentState != GameState::ended)
		{
			this->frame_manager.calculate_fps();

			this->processInput();


			this->quad_batch_.renderNow();

			this->window.swap_window();
		}
	}

	// process input
	void Core::processInput()
	{
		SDL_Event event{};

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				this->currentState = GameState::ended;
				break;
			case SDL_MOUSEMOTION:
				this->input_manager.setMousePosition(event.motion.x, event.motion.y);
				break;
			case SDL_KEYDOWN:
				this->input_manager.pressKey(event.key.keysym.sym);
				break;
			case SDL_KEYUP:
				this->input_manager.releaseKey(event.key.keysym.sym);
				break;
			case SDL_MOUSEBUTTONDOWN:
				this->input_manager.pressKey(event.button.button);
				//TODO use member var
				SoundEffect sound = this->audio.load_sound_effect("sound/shotgun.wav");
				sound.play();

				break;
			case SDL_MOUSEBUTTONUP:
				this->input_manager.releaseKey(event.button.button);
				SoundEffect sound2 = this->audio.load_sound_effect("sound/cg1.wav");
				sound2.play();
				break;
			}
		}


		if (this->input_manager.keyPressed(SDLK_w))
		{
			this->quad_batch_.camera.setPosition(this->quad_batch_.camera.getPosition() + glm::vec2(0.0, -5.0));
		}
		if (this->input_manager.keyPressed(SDLK_s))
		{
			this->quad_batch_.camera.setPosition(this->quad_batch_.camera.getPosition() + glm::vec2(0.0, 5.0));
		}

		if (this->input_manager.keyPressed(SDLK_a))
		{
			this->quad_batch_.camera.setPosition(this->quad_batch_.camera.getPosition() + glm::vec2(-5.0, 0.0));
		}
		if (this->input_manager.keyPressed(SDLK_d))
		{
			this->quad_batch_.camera.setPosition(this->quad_batch_.camera.getPosition() + glm::vec2(5.0, 0.0));
		}

		if (this->input_manager.keyPressed(SDLK_q))
		{
			this->quad_batch_.camera.setScale(this->quad_batch_.camera.getScale() + 0.1f);
		}
		if (this->input_manager.keyPressed(SDLK_e))
		{
			this->quad_batch_.camera.setScale(this->quad_batch_.camera.getScale() - 0.1f);
		}
		if (this->input_manager.keyPressed(SDL_BUTTON_LEFT))
		{
			glm::vec2 mouse_position = this->input_manager.get_mouse_position();
			mouse_position = this->quad_batch_.camera.global_to_local(mouse_position);
			cout << mouse_position.x << " :: " << mouse_position.y << endl;
		}
	}
}
