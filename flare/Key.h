#pragma once
#include <sdl/SDL.h>
#include "InputManager.h"

namespace Flare
{
	using namespace std;

	class Key
	{
	public:
		Key();
		~Key();

		void process();

		InputManager input_manager{};

		enum class GameState
		{
			running,
			ended
		};

		GameState currentState{GameState::running};
	private:
		SDL_Event event{};
	};
}
