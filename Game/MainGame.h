#pragma once


#include <dove/Quad.h>
#include <dove/GLSL.h>
#include <vector>
#include <dove/Window.h>
#include <dove/Camera.h>
#include <dove/QuadBatch.h>
using namespace std;

class MainGame
{
public:
	MainGame(int windowWdith, int windowHeight);
	~MainGame();

	void run();
	

private:

	
	


	Dove::Window window;
	Dove::GLSL colorProgram;
	Dove::Camera camera;
	Dove::QuadBatch quad_batch_;

	enum class GameState { running, ended };

	GameState currentState;

	Uint32 currentTicks;
	
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

