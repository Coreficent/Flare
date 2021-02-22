#include <iostream>

#include "Engine.h"

using namespace std;

Engine::Engine() : window{ nullptr }, currentState{GameState::running}, windowWidth{ 1024 }, windowHeight{ 700 }
{
}

Engine::~Engine()
{
}

void Engine::run()
{
	this->initialize();
}

void Engine::initialize()
{
	// sdl initialization
	SDL_Init(SDL_INIT_EVERYTHING);

	// window initialization
	this->window = SDL_CreateWindow(this->WINDOW_NAME, SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, this->windowWidth, this->windowHeight, SDL_WINDOW_OPENGL);

	// running the game logic
	this->gameLoop();
}

// main loop
void Engine::gameLoop()
{
	while(this->currentState!=GameState::ended)
	{
		this->processInput();
	}
}

// process input
void Engine::processInput()
{
	SDL_Event event{};

	while(SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			this->currentState = GameState::ended;
			break;
		case SDL_MOUSEMOTION:
			cout << event.motion.x << " " << event.motion.y << endl;
			break;
		}
	}
}
