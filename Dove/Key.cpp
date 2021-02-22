#include "Key.h"


namespace Dove
{
	using namespace std;


	Key::Key()
	{
	}


	Key::~Key()
	{
	}

	void Key::process()
	{
		while (SDL_PollEvent(&this->event))
		{
			switch (this->event.type)
			{
			case SDL_QUIT:
				this->currentState = GameState::ended;
				break;
			case SDL_MOUSEMOTION:
				this->input_manager.setMousePosition(this->event.motion.x, this->event.motion.y);
				break;
			case SDL_KEYDOWN:
				this->input_manager.pressKey(this->event.key.keysym.sym);
				break;
			case SDL_KEYUP:
				this->input_manager.releaseKey(this->event.key.keysym.sym);
				break;
			case SDL_MOUSEBUTTONDOWN:
				this->input_manager.pressKey(this->event.button.button);
				break;
			case SDL_MOUSEBUTTONUP:
				this->input_manager.releaseKey(this->event.button.button);

				break;
			}
		}
	}
}