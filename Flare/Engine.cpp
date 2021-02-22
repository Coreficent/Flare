#include "Engine.h"

Engine::Engine(): window{nullptr}, windowWidth{1024}, windowHeight{700}
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
}
