#include "Key.h"

namespace Flare
{
	using namespace std;

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
				this->input_manager.setMousePosition((float)this->event.motion.x, (float)this->event.motion.y);
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
			default:
				printf("unimplemented key");
				break;
			}
		}
	}
}
