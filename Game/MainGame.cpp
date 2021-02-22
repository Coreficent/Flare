#include <iostream>
#include <string>
#include <dove/error.h>
#include <array>

#include "MainGame.h"

#include <dove/Dove.h>
#include <Dove/ResourceManager.h>
using namespace std;


MainGame::MainGame(int windowWdith, int windowHeight) :window{}, camera { windowWdith, windowHeight }, quad_batch_{}, input_manager{}, frame_manager{}, currentState{ GameState::running }, currentTicks{ 0 },  windowWidth{ windowWdith }, windowHeight{ windowHeight }
{
}

MainGame::~MainGame()
{
}

void MainGame::run()
{
	this->initialize();



	// running the game logic
	this->gameLoop();
}

void MainGame::initialize()
{
	Dove::initialize();

	this->window.createWindow("Dove", this->windowWidth, this->windowHeight, 0);

	this->quad_batch_.initialize();
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
		
		this->frame_manager.calculateFPS();
		//this->timeTracker += 0.1f;
		this->processInput();
		this->camera.update();
		this->render();
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
			this->input_manager.pressKey(event.key.keysym.sym);
			break;
		case SDL_KEYUP:
			this->input_manager.releaseKey(event.key.keysym.sym);
			break;
		}
	}


	
	if (this->input_manager.keyPressed(SDLK_w)) {
		this->camera.setPosition(this->camera.getPosition() + glm::vec2(0.0, -5.0));
	}
	if (this->input_manager.keyPressed(SDLK_s)) {
		this->camera.setPosition(this->camera.getPosition() + glm::vec2(0.0, 5.0));
	}

	if (this->input_manager.keyPressed(SDLK_a)) {
		this->camera.setPosition(this->camera.getPosition() + glm::vec2(5.0, 0.0));
	}
	if (this->input_manager.keyPressed(SDLK_d)) {
		this->camera.setPosition(this->camera.getPosition() + glm::vec2(-5.0, 0.0));
	}

	if (this->input_manager.keyPressed(SDLK_q)) {
		this->camera.setScale(this->camera.getScale() + 0.1f);
	}
	if (this->input_manager.keyPressed(SDLK_e)) {
		this->camera.setScale(this->camera.getScale() - 0.1f);
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
	//auto location = this->colorProgram.getUniform("timeTracker");
	//glUniform1f(location, this->timeTracker);

	// camera location
	auto locationCamera = this->colorProgram.getUniform("cameraPosition");
	auto cameraMatrix = this->camera.getCameraMatrix();

	glUniformMatrix4fv(locationCamera, 1, GL_FALSE, &(cameraMatrix[0][0]));

	this->quad_batch_.begin();
	glm::vec4 position{ 0.0f,0.0f,50.0f,50.0f };
	glm::vec4 uv{ 0.0f,0.0f,1.0f,1.0f };
	static auto texture = Dove::ResourceManager::getTexture("texture/cake.png");
	Dove::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	for(auto i{0};i<5;++i)
	{
		this->quad_batch_.draw(position + glm::vec4{ 50.0f * i,0.0f,0.0f,0.0f }, uv, texture.id, 0.0f, color);
	}
	this->quad_batch_.end();
	this->quad_batch_.render();

	glBindTexture(GL_TEXTURE_2D, 0);
	this->colorProgram.unuse();

	this->window.swapBuffer();
}
