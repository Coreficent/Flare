#include <sdl/SDL.h>
#include "Dove.h"

namespace Dove
{
	void initialize()
	{
		// sdl initialization
		SDL_Init(SDL_INIT_EVERYTHING);

		// have two alternating buffers to render to smooth the rendering
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	}
}
