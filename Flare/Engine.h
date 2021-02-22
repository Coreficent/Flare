#pragma once

#include <sdl/SDL.h>
#include "Quad.h"
#include "GLSL.h"
#include <vector>

using namespace std;

class Engine
{
public:
	Engine();
	~Engine();

	void run();

private:
	const char* WINDOW_NAME{"Flare Engine"};

	
	SDL_Window* window;

	vector<Quad*> quads;

	GLSL colorProgram;

	enum class GameState { running, ended };

	GameState currentState;

	float time;

	int windowWidth;
	int windowHeight;

	void initialize();
	void initializeShader();
	void gameLoop();
	void processInput();
	void render();
};

