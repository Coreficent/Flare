#include "Context.h"
#include <sdl/SDL.h>


Context::Context()
{
	SDL_Init(SDL_INIT_EVERYTHING);
}


Context::~Context()
{
	SDL_Quit();
}
