#include "Media.h"
#include <sdl/SDL.h>


Media::Media()
{
	SDL_Init(SDL_INIT_EVERYTHING);
}


Media::~Media()
{
	SDL_Quit();
}
