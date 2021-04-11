#pragma once

#include <glm/detail/type_vec2.hpp>
#include <sdl/SDL.h>
#include <unordered_map>

namespace Flare
{
	using namespace glm;
	using namespace std;

	class Key
	{

	public:
		static void process();
		static bool is_down(unsigned int key_id);
		static void press_key(unsigned int key_id);
		static void release_key(unsigned int key_id);

		enum class Game_state
		{
			running,
			ending
		};

		inline static Game_state state{ Game_state::running };
		inline static vec2 mouse_position{};

	private:
		inline static SDL_Event event{};
		inline static unordered_map<unsigned int, bool> keymap{};

	};
}
