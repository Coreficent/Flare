#pragma once
#include <sdl/SDL.h>
#include <string>

namespace Dove
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

		int createWindow(std::string windowName, int windowWidth, int windowHeight, unsigned int windowFlag);
		int getScreenWidth();
		int getScreenHeight();

		void swapBuffer() const;
	private:
		SDL_Window* window;
	};
}
