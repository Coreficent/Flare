#pragma once

#include <sdl/SDL.h>
#include <string>

namespace Flare
{
	using namespace std;

	enum WindowFlags
	{
		INVISIBLE = 0x1,
		FULLSCREEN = 0x2,
		BORDERLESS = 0x4
	};

	class Window
	{

	public:
		Window(string name, int window_width, int window_height);

		void update_window() noexcept;

		bool full_screen{ false };
		bool hidden{ false };
		bool borderless{ false };

		int windows_width{};
		int windows_height{};

	private:
		SDL_Window* window;

	};
}
