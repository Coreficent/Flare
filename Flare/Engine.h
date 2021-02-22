#pragma once

#include <sdl/SDL.h>
#include <gl/glew.h>

class Engine
{
public:
	Engine();
	~Engine();

	void run();
	void initialize();

private:
	const char* WINDOW_NAME{"Flare Engine"};

	SDL_Window* window;

	int windowWidth;
	int windowHeight;
};

