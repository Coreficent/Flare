#pragma once

#include <sdl/SDL.h>
#include <gl/glew.h>
#include "Quad.h"


class Engine
{
public:
	Engine();
	~Engine();

	void run();
	

private:
	const char* WINDOW_NAME{"Flare Engine"};

	enum class GameState { running, ended };

	SDL_Window* window;

	GameState currentState;

	int windowWidth;
	int windowHeight;

	void initialize();
	void gameLoop();
	void processInput();
	void render();

	Quad quad;
};

