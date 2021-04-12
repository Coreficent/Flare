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
				Key::press_key(SDL_QUIT);
				break;
			case SDL_MOUSEMOTION:
				Key::mouse_position = vec2{ Key::event.motion.x, Key::event.motion.y };
				break;
			case SDL_KEYDOWN:
				Key::press_key(Key::event.key.keysym.sym);
				break;
			case SDL_KEYUP:
				Key::release_key(Key::event.key.keysym.sym);
				break;
			case SDL_MOUSEBUTTONDOWN:
				Key::press_key(Key::event.button.button);
				break;
			case SDL_MOUSEBUTTONUP:
				Key::release_key(Key::event.button.button);
				break;
			default:
				break;
			}
		}
	}

	bool Key::is_down(unsigned int key_id)
	{
		auto it = Key::keymap.find(key_id);
		return it != Key::keymap.end() ? it->second : false;
	}

	void Key::press_key(unsigned int key_id)
	{
		Key::keymap[key_id] = true;
	}


	void Key::release_key(unsigned int key_id)
	{
		Key::keymap[key_id] = false;
	}
}
