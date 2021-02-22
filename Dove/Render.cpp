#include "Render.h"
#include <gl/glew.h>
#include <sdl/SDL.h>
#include "debug.h"


namespace Dove
{
	using namespace std;
	Render::Render()
	{
	}


	Render::~Render()
	{
	}

	void Render::initialize()
	{		//First you need to create a valid OpenGL rendering context and call glewInit() to initialize the extension entry points.
		if (glewInit() != GLEW_OK)
		{
			dout << "glew failed" << endl;
		}

		dout << "OpenGL version: " << glGetString(GL_VERSION) << endl;

		//background: color to clear to
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

		// vertical synch 0 off 1 on
		SDL_GL_SetSwapInterval(0);

		//blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
}
