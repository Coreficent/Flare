#include <iostream>
#include <string>
#include <dove/error.h>
#include <array>

#include "MainGame.h"

#include <dove/Dove.h>
using namespace std;


MainGame::MainGame(int windowWdith, int windowHeight) : quads{}, window{}, camera{windowWdith, windowHeight}, currentState{GameState::running}, currentTicks{0}, timeTracker{0.0f}, fps{0}, frameTime{0}, budget{16}, windowWidth{windowWdith},windowHeight{windowHeight}
{
}

MainGame::~MainGame()
{
}

void MainGame::run()
{
	this->initialize();


	this->quads.push_back(new Dove::Quad{0.0f, 0.0f, 100.0f, 100.0f});
	this->quads.push_back(new Dove::Quad{250.0f, 250.0f, 250.0f, 250.0f});
	this->quads[0]->initialize("texture/cake.png");
	this->quads[1]->initialize("texture/cake.png");

	// running the game logic
	this->gameLoop();
}

void MainGame::initialize()
{
	Dove::initialize();

	this->window.createWindow("Dove", this->windowWidth, this->windowHeight, 0);


	this->initializeShader();
}

void MainGame::initializeShader()
{
	this->colorProgram.compileShader("shader/colorShade.sv", "shader/colorShade.sf");
	this->colorProgram.addAttribute("vertexPosition");
	this->colorProgram.addAttribute("vertexColor");
	this->colorProgram.addAttribute("vertexUV");
	this->colorProgram.linkShader();
}

// main loop
void MainGame::gameLoop()
{
	while (this->currentState != GameState::ended)
	{
		
		this->calculateFPS();
		//auto startTick = SDL_GetTicks();
		this->timeTracker += 0.1f;
		this->processInput();
		this->camera.update();
		this->render();
		
		//auto frameTicks = SDL_GetTicks() - startTick;


		//if (this->budget > frameTicks)
		//{
		//	SDL_Delay(this->budget - frameTicks);
		//}
	}
}

// process input
void MainGame::processInput()
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

		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_w:
				this->camera.setPosition(this->camera.getPosition() + glm::vec2(0.0, -5.0));
				break;
			case SDLK_s:
				this->camera.setPosition(this->camera.getPosition() + glm::vec2(0.0, 5.0));
				break;

			case SDLK_a:
				this->camera.setPosition(this->camera.getPosition() + glm::vec2(5.0, 0.0));
				break;
			case SDLK_d:
				this->camera.setPosition(this->camera.getPosition() + glm::vec2(-5.0, 0.0));
				break;

			case SDLK_q:
				this->camera.setScale(this->camera.getScale() + 0.1f);
				break;
			case SDLK_e:
				this->camera.setScale(this->camera.getScale() - 0.1f);
				break;
			}

			break;
		}
	}
}

// render
void MainGame::render()
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

	// camera location
	auto locationCamera = this->colorProgram.getUniform("cameraPosition");
	auto cameraMatrix = this->camera.getCameraMatrix();

	glUniformMatrix4fv(locationCamera, 1, GL_FALSE, &(cameraMatrix[0][0]));

	for (auto& i: this->quads)
	{
		i->draw();
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	this->colorProgram.unuse();

	this->window.swapBuffer();
}

void MainGame::calculateFPS()
{
	static const auto SAMPLE_SIZE{50};
	static array<Uint32, SAMPLE_SIZE> frameTimes{0,0,0};
	static auto currentFrame{0};
	static auto previousTicks = SDL_GetTicks();

	this->currentTicks = SDL_GetTicks();
	this->frameTime = this->currentTicks - previousTicks;
	previousTicks = this->currentTicks;
	
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
		Dove::debugPrint("fps: ");
		printf("%f\n", this->fps);
	}
	auto frameTicks = SDL_GetTicks() - this->currentTicks;
	if (this->budget > frameTicks)
	{
		SDL_Delay(this->budget - frameTicks);
	}
}
