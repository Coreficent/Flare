#include "Window.h"
#include <gl/glew.h>
#include "error.h"

namespace Dove
{
	using namespace std;

	Window::Window() : window{nullptr}
	{
	}


	Window::~Window()
	{
	}

	int Window::getScreenWidth()
	{
		return 0;
	}

	int Window::getScreenHeight()
	{
		return 0;
	}

	void Window::swapBuffer() const
	{
		SDL_GL_SwapWindow(this->window);
	}

	int Window::createWindow(string windowName, int windowWidth, int windowHeight, unsigned int windowFlag)
	{
		Uint32 flag = SDL_WINDOW_OPENGL;
		if (windowFlag & INVISIBLE)
		{
			flag |= SDL_WINDOW_HIDDEN;
		}
		if (windowFlag & FULLSCREEN)
		{
			flag |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}
		if (windowFlag & BORDERLESS)
		{
			flag |= SDL_WINDOW_BORDERLESS;
		}

		// window initialization
		this->window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, flag);

		if (!this->window)
		{
			fatalError("sdl window failed");
		}

		auto glContext = SDL_GL_CreateContext(this->window);
		if (!glContext)
		{
			fatalError("sdl context failed");
		}

		auto glError = glewInit();
		if (glError != GLEW_OK)
		{
			fatalError("glew failed");
		}

		debugPrint("opengl version");
		printf("%s\n", reinterpret_cast<const char*>(glGetString(GL_VERSION)));

		//background: color to clear to
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);


		// vertical synch 0 off 1 on
		SDL_GL_SetSwapInterval(0);

		return 0;
	}
}
