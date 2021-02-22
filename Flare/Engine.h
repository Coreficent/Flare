#pragma once

#include <sdl/SDL.h>
#include "Quad.h"
#include "GLSL.h"
#include "GlTexture.h"

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

	Quad quad;
	GLSL colorProgram;
	GLTexture cakeTexture;

	float time;

	int windowWidth;
	int windowHeight;

	void initialize();
	void initializeShader();
	void gameLoop();
	void processInput();
	void render();
};

