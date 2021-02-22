#include <iostream>
#include <string>

#include "Engine.h"

using namespace std;

void fatalError(string errorString)
{
	cout << errorString << endl;
	int a;
	cin >> a;
	SDL_Quit();
}

Engine::Engine() : window{ nullptr }, currentState{GameState::running}, windowWidth{ 1024 }, windowHeight{ 700 },quad{ -1.0f,-1.0f,1.0f,1.0f}
{
}

Engine::~Engine()
{
}

void Engine::run()
{
	this->initialize();

	quad.initialize();

	// running the game logic
	this->gameLoop();
}

void Engine::initialize()
{
	// sdl initialization
	SDL_Init(SDL_INIT_EVERYTHING);

	// window initialization
	this->window = SDL_CreateWindow(this->WINDOW_NAME, SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, this->windowWidth, this->windowHeight, SDL_WINDOW_OPENGL);

	if(this->window == nullptr)
	{
		fatalError("sdl window failed");
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(this->window);
	if(glContext == nullptr)
	{
		fatalError("sdl context failed");
	}

	GLenum glError = glewInit();
	if(glError != GLEW_OK)
	{
		fatalError("glew failed");
	}

	// have two alternating buffers to render to smooth the rendering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//background: color to clear to
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

	
}

// main loop
void Engine::gameLoop()
{
	while(this->currentState!=GameState::ended)
	{
		this->processInput();
		this->render();
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

// render
void Engine::render()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	quad.draw();

	SDL_GL_SwapWindow(this->window);
}
