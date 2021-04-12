#include "Window.h"
#include "debug.h"

#include <gl/glew.h>

namespace Flare
{
	using namespace std;

	Window::Window(string name, int windows_width, int windows_height) : window{ nullptr }, windows_width{ windows_width }, windows_height{ windows_height }
	{
		//Use this function to set an OpenGL window attribute before window creation. 
		if (SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) != 0)
		{
			dout << "window set attribute failed: " << SDL_GetError() << endl;
		}

		Uint32 flag = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

		if (this->full_screen)
		{
			flag |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}
		if (this->hidden)
		{
			flag |= SDL_WINDOW_HIDDEN;
		}
		if (this->borderless)
		{
			flag |= SDL_WINDOW_BORDERLESS;
		}

		this->window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->windows_width, this->windows_height, flag);

		if (!this->window)
		{
			dout << "window failed to open" << endl;
		}

		if (!SDL_GL_CreateContext(this->window))
		{
			dout << "sdl context failed" << endl;
		}

		//First you need to create a valid OpenGL rendering context and call glewInit() to initialize the extension entry points.
		if (glewInit() != GLEW_OK)
		{
			dout << "glew failed" << endl;
		}

		dout << "OpenGL version: " << glGetString(GL_VERSION) << endl;

		//background: color to clear to
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

		// vertical synch 0 off 1 on
		SDL_GL_SetSwapInterval(0);

		//blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void Window::update_window() noexcept
	{
		SDL_GL_SwapWindow(this->window);
		SDL_GetWindowSize(this->window, &this->windows_width, &this->windows_height);
	}
}
