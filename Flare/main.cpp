#include <iostream>
#include "Engine.h"


int main(int argc, char ** argv)
{
	//SDL_Init(SDL_INIT_EVERYTHING);
	Engine engine{};
	engine.run();

	return 0;
}
