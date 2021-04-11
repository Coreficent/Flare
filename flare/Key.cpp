#include "Key.h"

namespace Flare
{
	using namespace std;

	void Key::process()
	{
		while (SDL_PollEvent(&Key::event))
		{
			switch (Key::event.type)
			{
			case SDL_QUIT:
				Key::currentState = GameState::ended;
				break;
			case SDL_MOUSEMOTION:
				Key::input_manager.setMousePosition((float)Key::event.motion.x, (float)Key::event.motion.y);
				break;
			case SDL_KEYDOWN:
				Key::input_manager.pressKey(Key::event.key.keysym.sym);
				break;
			case SDL_KEYUP:
				Key::input_manager.releaseKey(Key::event.key.keysym.sym);
				break;
			case SDL_MOUSEBUTTONDOWN:
				Key::input_manager.pressKey(Key::event.button.button);
				break;
			case SDL_MOUSEBUTTONUP:
				Key::input_manager.releaseKey(Key::event.button.button);
				break;
			default:
				printf("unimplemented key");
				break;
			}
		}
	}
}
