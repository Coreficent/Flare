#pragma once


#include <dove/Quad.h>
#include <dove/GLSL.h>
#include <vector>
#include <Dove/Window.h>

using namespace std;

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();
	

private:

	
	Dove::Window window;

	vector<Dove::Quad*> quads;

	Dove::GLSL colorProgram;

	enum class GameState { running, ended };

	GameState currentState;

	float timeTracker;
	
	
	float fps;
	unsigned int frameTime;
	unsigned int budget;

	int windowWidth;
	int windowHeight;

	void initialize();
	void initializeShader();
	void gameLoop();
	void processInput();
	void render();
	void calculateFPS();
};

