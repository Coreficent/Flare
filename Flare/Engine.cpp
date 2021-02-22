#include <iostream>
#include <string>

#include "Engine.h"
#include "error.h"
#include <array>

using namespace std;


Engine::Engine() : window{nullptr}, quads{}, currentState{GameState::running}, timeTracker{0.0f}, fps{0}, frameTime{0}, budget{16}, windowWidth{1024}, windowHeight{700}
{
}

Engine::~Engine()
{
}

void Engine::run()
{
	this->initialize();


	this->quads.push_back(new Quad{0.0f, 0.0f, 1.0f, 1.0f});
	this->quads.push_back(new Quad{-1.0f, -1.0f, 1.0f, 1.0f});
	this->quads[0]->initialize("texture/cake.png");
	this->quads[1]->initialize("texture/cake.png");

	// running the game logic
	this->gameLoop();
}

void Engine::initialize()
{
	// sdl initialization
	SDL_Init(SDL_INIT_EVERYTHING);

	// have two alternating buffers to render to smooth the rendering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// window initialization
	this->window = SDL_CreateWindow(this->WINDOW_NAME, SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, this->windowWidth, this->windowHeight, SDL_WINDOW_OPENGL);

	if (!this->window)
	{
		fatalError("sdl window failed");
	}

	auto glContext = SDL_GL_CreateContext(this->window);
	if (!glContext)
	{
		fatalError("sdl context failed");
	}

	auto glError = glewInit();
	if (glError != GLEW_OK)
	{
		fatalError("glew failed");
	}

	debugPrint("opengl version");
	printf("%s\n", reinterpret_cast<const char*>(glGetString(GL_VERSION)));

	//background: color to clear to
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);


	// vertical synch 0 off 1 on
	SDL_GL_SetSwapInterval(0);

	this->initializeShader();
}

void Engine::initializeShader()
{
	this->colorProgram.compileShader("shader/colorShade.vert", "shader/colorShade.frag");
	this->colorProgram.addAttribute("vertexPosition");
	this->colorProgram.addAttribute("vertexColor");
	this->colorProgram.addAttribute("vertexUV");
	this->colorProgram.linkShader();
}

// main loop
void Engine::gameLoop()
{
	while (this->currentState != GameState::ended)
	{
		auto startTick = SDL_GetTicks();
		this->timeTracker += 0.1f;
		this->processInput();
		this->render();
		this->calculateFPS();
		auto frameTicks = SDL_GetTicks() - startTick;
		if (this->budget > frameTicks)
		{
			//SDL_Delay(this->budget - frameTicks);
		}
	}
}

// process input
void Engine::processInput()
{
	SDL_Event event{};

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			this->currentState = GameState::ended;
			break;
		case SDL_MOUSEMOTION:
			//cout << event.motion.x << " " << event.motion.y << endl;
			break;
		}
	}
}

// render
void Engine::render()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	this->colorProgram.use();
	glActiveTexture(GL_TEXTURE0);

	auto textureLocation = this->colorProgram.getUniform("cakeSampler");
	glUniform1i(textureLocation, 0);

	// update timeTracker
	auto location = this->colorProgram.getUniform("timeTracker");
	glUniform1f(location, this->timeTracker);


	for (auto& i: this->quads)
	{
		i->draw();
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	this->colorProgram.unuse();

	SDL_GL_SwapWindow(this->window);
}

void Engine::calculateFPS()
{
	static const auto SAMPLE_SIZE{50};
	static array<Uint32, SAMPLE_SIZE> frameTimes{0,0,0};
	static auto currentFrame{0};
	static auto previousTicks = SDL_GetTicks();

	auto currentTicks = SDL_GetTicks();
	this->frameTime = currentTicks - previousTicks;
	previousTicks = currentTicks;

	frameTimes[currentFrame++ % SAMPLE_SIZE] = this->frameTime;

	auto averageFrameTime{0.0f};
	for (auto& i : frameTimes)
	{
		averageFrameTime += i;
	}
	averageFrameTime = averageFrameTime / SAMPLE_SIZE + 0.0001f;
	this->fps = 1000.0f / averageFrameTime;

	if (!(currentFrame % 60))
	{
		debugPrint("fps: ");
		printf("%f\n", this->fps);
	}
}
