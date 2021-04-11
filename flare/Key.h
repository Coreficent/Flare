#pragma once
#include <sdl/SDL.h>
#include "InputManager.h"

namespace Flare
{
	using namespace std;

	class Key
	{

	public:
		static void process();

		enum class GameState
		{
			running,
			ended
		};

		inline static GameState currentState{ GameState::running };
		inline static InputManager input_manager{};
		
	private:
		inline static SDL_Event event{};

	};
}
