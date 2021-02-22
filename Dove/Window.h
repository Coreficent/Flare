#pragma once
#include <sdl/SDL.h>
#include <string>

namespace Flare
{
	enum WindowFlags
	{
		INVISIBLE = 0x1,
		FULLSCREEN = 0x2,
		BORDERLESS = 0x4
	};

	class Window
	{
	public:
		Window();
		~Window();

		void initialize(std::string name, int width, int height);
		void swap_window() const;

		bool full_screen{false};
		bool hidden{false};
		bool borderless{false};

	private:
		SDL_Window* window;
	};
}
