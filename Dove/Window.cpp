#include "Window.h"
#include <gl/glew.h>
#include "error.h"
#include "Header.h"
#include <iostream>

namespace Dove
{
	using namespace std;

	Window::Window() : window{nullptr}
	{
		//Use this function to set an OpenGL window attribute before window creation. 
		if (SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) != 0)
		{
			dout << "window set attribute failed: " << SDL_GetError() << endl;
		}
	}


	Window::~Window()
	{
	}


	void Window::swap_window() const
	{
		SDL_GL_SwapWindow(this->window);
	}

	void Window::open_window(string name, int width, int height)
	{
		Uint32 flag = SDL_WINDOW_OPENGL;
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

		this->window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flag);

		if (!this->window)
		{
			dout << "window failed to open" << endl;
		}

		auto glContext = SDL_GL_CreateContext(this->window);
		if (!glContext)
		{
			output_error("sdl context failed");
		}

		auto glError = glewInit();
		if (glError != GLEW_OK)
		{
			output_error("glew failed");
		}

		debug_print("opengl version");
		printf("%s\n", reinterpret_cast<const char*>(glGetString(GL_VERSION)));

		//background: color to clear to
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);


		// vertical synch 0 off 1 on
		SDL_GL_SetSwapInterval(0);

		//blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
}
